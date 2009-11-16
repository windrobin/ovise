/********************************************************************************
 * Name:      QualifiedNameRegister.h											*
 * Purpose:   Implements a singleton class holding strings as parts of 			*
 *			  qualified names. These parts are: native name, generic name and 	*
 *			  genic hint.The generic name is unique and acts as hash-key.		*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-02														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#include "QualifiedNameRegister.h"

QualifiedNameRegister* QualifiedNameRegister::instance = 0;
QualifiedNameRegister::QualifiedNameRegister(void)
{
	this->AllocatedGenericNames = HashMap_wxString();
	this->StoredGenericHints = HashMap_wxString();
}

QualifiedNameRegister::~QualifiedNameRegister(void)
{
	this->AllocatedGenericNames.clear();
	this->StoredGenericHints.clear();
}
QualifiedNameRegister* QualifiedNameRegister::GetSingletonPtr()
{
	if (QualifiedNameRegister::instance == 0) QualifiedNameRegister::instance = new QualifiedNameRegister();
	return QualifiedNameRegister::instance;
}