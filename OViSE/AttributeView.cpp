
#include "AttributeView.h"
#include <boost/foreach.hpp>
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/finder.hpp>




namespace {

// Delim string for vector textualization
const char* Vds = "; ";

template < int n, class VectorType >
bool ParseVector( const std::string& Str, VectorType& Dst )
{
	using namespace boost::algorithm;
	split_iterator<std::string::const_iterator> Current=
		make_split_iterator(Str,token_finder(is_any_of(";")));


	for ( int i=0; i<n; ++i )
	{
		// No more numbers to read?
		if ( Current.eof() )
			return false;

		std::string Range( Current->begin(), Current->end() );
		trim(Range);

		try {
			float x = boost::lexical_cast<float>(Range);
			Dst[i]=x;
		}
		catch(boost::bad_lexical_cast&)
		{
			return false;
		}
		Current++;
	}
	return true;
}

/** Type visitor to set attributes in the Entity.
*/
struct SetAttributeVisitor :
	public boost::static_visitor<void>
{
public:
	SetAttributeVisitor( wxPGProperty* Prop ) :Prop(Prop) {}

	void operator()(Entity*) const
	{
	}

	void operator()(std::string& String) const
	{
		String = Prop->GetValueRef().GetString();
	}

	void operator()(int& Integer) const
	{
		Integer = Prop->GetValueRef().GetInteger();
	}

	void operator()(double& Double) const
	{
		Double = Prop->GetValueRef().GetDouble();
	}

	void operator()(vec2& Lhs) const
	{
		std::string Str( Prop->GetValueRef().GetString().mb_str() );
		ParseVector<2>(Str, Lhs);
	}

	void operator()(vec3& Lhs) const
	{
		std::string Str( Prop->GetValueRef().GetString().mb_str() );
		ParseVector<3>(Str, Lhs);
	}

	void operator()(vec4& Lhs) const
	{
		std::string Str( Prop->GetValueRef().GetString().mb_str() );
		ParseVector<4>(Str, Lhs);
	}

	void operator()(quat& Lhs) const
	{
		std::string Str( Prop->GetValueRef().GetString().mb_str() );
		ParseVector<4>(Str, Lhs);
	}

	void operator()(boost::any& Any) const
	{
	}
private:
	wxPGProperty* Prop;
};

/** Type visitor to display entity attributes in a property grid.
*/
class GetAttributeVisitor :
	public boost::static_visitor<wxPGProperty*>
{
public:
	GetAttributeVisitor( const wxString& Name ) : Name(Name) {}

	wxPGProperty* operator()(Entity*) const	{ return 0; }


	wxPGProperty* operator()(const std::string & String) const
	{return new wxStringProperty(Name, wxPG_LABEL, String);}

	wxPGProperty* operator()(int Integer) const
	{
		return new wxIntProperty(Name, wxPG_LABEL,Integer);
	}

	wxPGProperty* operator()(double Double) const
	{
		return new wxFloatProperty(Name, wxPG_LABEL, Double);
	}

	wxPGProperty* operator()(const boost::any& Any) const
	{
		return 0;
	}

	wxPGProperty* operator()(const vec2& Rhs) const
	{
		std::ostringstream Str;
		Str << Rhs.x << Vds << Rhs.y;

		return new wxStringProperty(Name, wxPG_LABEL, Str.str());
	}

	wxPGProperty* operator()(const vec3& Rhs) const
	{
		std::ostringstream Str;
		Str << Rhs.x << Vds << Rhs.y << Vds << Rhs.z;

		return new wxStringProperty(Name, wxPG_LABEL, Str.str());
	}

	wxPGProperty* operator()(const vec4& Rhs) const
	{
		std::ostringstream Str;
		Str << Rhs.x << Vds << Rhs.y << Vds << Rhs.z << Vds << Rhs.w;

		return new wxStringProperty(Name, wxPG_LABEL, Str.str());
	}

	wxPGProperty* operator()(const quat& Rhs) const
	{
		std::ostringstream Str;
		Str << Rhs.w << Vds << Rhs.x << Vds << Rhs.y << Vds << Rhs.z;

		return new wxStringProperty(Name, wxPG_LABEL, Str.str());
	}



private:
	wxString Name;
};

}

AttributeView::AttributeView(wxWindow* Parent)
: mObjectProperties(0), mCurrentEntity(0)
{
	mObjectProperties = new wxPropertyGrid(Parent, wxID_ANY, wxDefaultPosition, wxSize(300, -1));
	mObjectProperties->Bind( wxEVT_PG_CHANGED, &AttributeView::OnPropertyChange, this );
	mObjectProperties->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);
	mObjectProperties->SetSplitterLeft(true);
}

AttributeView::~AttributeView()
{
}

wxPropertyGrid* AttributeView::GetGrid()
{
	return mObjectProperties;
}

void AttributeView::ShowAttribs()
{
	mObjectProperties->Clear();

	if ( !mCurrentEntity )
		return;

	// Read all attribute variants and set them as property values
	typedef Entity::ValueType ValueType;
	BOOST_FOREACH( const ValueType& x, mCurrentEntity->GetAttributes() )
	{
		wxPGProperty* Prop = boost::apply_visitor( GetAttributeVisitor(x.first), x.second );

		// Can we display this?
		if ( Prop )
			mObjectProperties->Append( Prop );
	}
}

void AttributeView::OnEntityAttributeChanged(
		Entity* Rhs,
		const std::string& Name,
		const EntityVariantType* Attribute
	)
{
	BOOST_ASSERT( Rhs == mCurrentEntity );

	// FIXME: instead of updating the whole attribute view, only update the one that has actually changed.
	ShowAttribs();
}

void AttributeView::SetEntity( Entity* Rhs )
{
	if ( mCurrentEntity )
		mCurrentEntity->RemoveObserver( this );

	mCurrentEntity = Rhs;

	if ( Rhs )
		Rhs->InsertObserver( this );


	ShowAttribs();
}

void AttributeView::OnPropertyChange(wxPropertyGridEvent& event)
{
	wxPGProperty* Property = event.GetProperty();

	// Shouldn't get change messages when nothing is selected
	BOOST_ASSERT( mCurrentEntity );
	
	// Find the corresponding attribute in the currently selected entity
	std::string AttribName(Property->GetName());
	const Entity::VariantType* AttributePointer=mCurrentEntity->GetAttribute( AttribName );
	
	// The attribute should exist!
	BOOST_ASSERT( AttributePointer );

	// Copy the values
	Entity::VariantType Attribute = *AttributePointer;
	boost::apply_visitor( SetAttributeVisitor(Property), Attribute );
	
	// Update the attribute
	mCurrentEntity->SetAttribute( AttribName, Attribute ); 
}
