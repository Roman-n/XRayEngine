﻿#include "stdafx.h"
#include "bloodsucker_state_manager.h"
#include "bloodsucker.h"

#include "../control_animation_base.h"
#include "../control_direction_base.h"
#include "../control_movement_base.h"
#include "../control_path_builder_base.h"

#include "../states/monster_state_rest.h"
#include "../states/monster_state_attack.h"
#include "../states/monster_state_panic.h"
#include "../states/monster_state_eat.h"
#include "../states/monster_state_hear_int_sound.h"
#include "../states/monster_state_hitted.h"

#include "bloodsucker_vampire.h"
#include "bloodsucker_predator.h"
#include "bloodsucker_state_capture_jump.h"
#include "bloodsucker_attack_state.h"

CStateManagerBloodsucker::CStateManagerBloodsucker(CAI_Bloodsucker* monster): inherited(monster)
{
    add_state(eStateCustom, xr_new<CStateCaptureJumpBloodsucker<CAI_Bloodsucker>>(monster));
    add_state(eStateRest, xr_new<CStateMonsterRest<CAI_Bloodsucker>>(monster));
    add_state(eStatePanic, xr_new<CStateMonsterPanic<CAI_Bloodsucker>>(monster));
    add_state(eStateAttack, xr_new<CBloodsuckerStateAttack<CAI_Bloodsucker>>(monster));
    add_state(eStateEat, xr_new<CStateMonsterEat<CAI_Bloodsucker>>(monster));
    add_state(eStateHearInterestingSound, xr_new<CStateMonsterHearInterestingSound<CAI_Bloodsucker>>(monster));
    add_state(eStateHitted, xr_new<CStateMonsterHitted<CAI_Bloodsucker>>(monster));
    add_state(eStateCustom_Vampire, xr_new<CStateBloodsuckerVampire<CAI_Bloodsucker>>(monster));
}

void CStateManagerBloodsucker::drag_object()
{
    CEntityAlive* const ph_obj = object->m_cob;
    if (!ph_obj)
    {
        return;
    }

    IKinematics* const kinematics = smart_cast<IKinematics*>(ph_obj->Visual());
    if (!kinematics)
    {
        return;
    }

    CMonsterSquad* const squad = monster_squad().get_squad(object);
    if (squad)
    {
        squad->lock_corpse(ph_obj);
    }

    {
        const u16 drag_bone = kinematics->LL_BoneID(object->m_str_cel);
        object->character_physics_support()->movement()->PHCaptureObject(ph_obj, drag_bone);
    }

    CPHCapture* const capture = object->character_physics_support()->movement()->PHCapture();

    if (capture && !capture->Failed() && object->is_animated())
    {
        object->start_drag();
    }
}

void CStateManagerBloodsucker::update()
{
    inherited::update();
}

void CStateManagerBloodsucker::execute()
{
    u32                 state_id = u32(-1);

    const CEntityAlive* enemy    = object->EnemyMan.get_enemy();

    if (!object->is_drag_anim_jump() && !object->is_animated())
    {
        if (enemy)
        {
            if (check_state(eStateCustom_Vampire))
            {
                state_id = eStateCustom_Vampire;
            }
            else
            {
                switch (object->EnemyMan.get_danger_type())
                {
                    case eStrong:
                        state_id = eStatePanic;
                        break;
                    case eWeak:
                        state_id = eStateAttack;
                        break;
                }
            }
        }
        else if (object->HitMemory.is_hit())
        {
            state_id = eStateHitted;
        }
        else if (object->hear_interesting_sound)
        {
            state_id = eStateHearInterestingSound;
        }
        else
        {
            if (can_eat())
                state_id = eStateEat;
            else
                state_id = eStateRest;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Additional
        ///////////////////////////////////////////////////////////////////////////////

        // check if start interesting sound state
        // 		if ( (prev_substate != eStateHearInterestingSound) && (state_id == eStateHearInterestingSound) )
        // 		{
        // 			object->start_invisible_predator();
        // 		}
        // 		else
        // 		// check if stop interesting sound state
        // 		if ( (prev_substate == eStateHearInterestingSound) && (state_id != eStateHearInterestingSound) )
        // 		{
        // 			object->stop_invisible_predator();
        // 		}

        select_state(state_id);

        // выполнить текущее состояние
        get_state_current()->execute();

        prev_substate = current_substate;
    }
    else
    {
        state_id = eStateCustom;

        if (object->is_drag_anim_jump())
        {
            select_state(state_id);

            // выполнить текущее состояние
            get_state_current()->execute();

            prev_substate = current_substate;

            drag_object();
        }
    }
}
