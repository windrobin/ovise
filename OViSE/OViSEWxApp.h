/***************************************************************
 * Name:      OViSEWxApp.h
 * Purpose:   Defines Application Class
 * Author:    Alexander Kasper (akasper@ira.uka.de)
 * Created:   2008-09-11
 * Copyright: Alexander Kasper (http://i61www.ira.uka.de/users/akasper)
 * License:
 **************************************************************/

#ifndef OVISEWXAPP_H
#define OVISEWXAPP_H

#include <wx/app.h>
#include <wx/splash.h>
#include <Ogre.h>

class OViSEWxApp : public wxApp
{
    public:
        virtual bool OnInit();
		virtual ~OViSEWxApp();

	private:
		Ogre::Root *mRoot;
};

#endif // OVISEWXAPP_H
