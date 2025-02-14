﻿////////////////////////////////////////////////////////////////////////////
//	Module 		: property_converter_color.hpp
//	Created 	: 11.12.2007
//  Modified 	: 11.12.2007
//	Author		: Dmitriy Iassenev
//	Description : property converter color class
////////////////////////////////////////////////////////////////////////////

#ifndef PROPERTY_CONVERTER_COLOR_HPP_INCLUDED
#define PROPERTY_CONVERTER_COLOR_HPP_INCLUDED

public
ref class property_converter_color: public System::ComponentModel::TypeConverter
{
private:
    typedef System::ComponentModel::TypeConverter                inherited;
    typedef System::ComponentModel::PropertyDescriptorCollection PropertyDescriptorCollection;
    typedef System::ComponentModel::ITypeDescriptorContext       ITypeDescriptorContext;
    typedef System::Object                                       Object;
    typedef System::Attribute                                    Attribute;
    typedef System::Globalization::CultureInfo                   CultureInfo;
    typedef System::Type                                         Type;

public:
    typedef System::ComponentModel::TypeConverter::StandardValuesCollection StandardValuesCollection;

public:
    virtual PropertyDescriptorCollection ^ GetProperties(ITypeDescriptorContext ^ context, Object ^ value, array<Attribute ^> ^ attributes) override;
    virtual bool GetPropertiesSupported(ITypeDescriptorContext ^ context) override;

public:
    virtual bool CanConvertTo(ITypeDescriptorContext ^ context, Type ^ destination_type) override;
    virtual Object ^ ConvertTo(ITypeDescriptorContext ^ context, CultureInfo ^ culture, Object ^ value, Type ^ destination_type) override;
    virtual bool CanConvertFrom(ITypeDescriptorContext ^ context, Type ^ source_type) override;
    virtual Object ^ ConvertFrom(ITypeDescriptorContext ^ context, CultureInfo ^ culture, Object ^ value) override;
};   // ref class property_converter_color

#endif   // ifndef PROPERTY_CONVERTER_COLOR_HPP_INCLUDED
