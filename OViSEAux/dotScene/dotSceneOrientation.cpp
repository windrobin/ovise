#ifndef dotSceneOrientation_h_
#define dotSceneOrientation_h_
#include "dotSceneOrientation.h"
#endif

#ifndef math_h_
#define math_h_
#include <math.h>
#endif

using namespace dotSceneObjects;

dotSceneAngleAxis dotSceneObjects::dotSceneOrientation::get_AngleAxis() const { return this->_AngleAxis; }
dotSceneAxisXYZ dotSceneObjects::dotSceneOrientation::get_AxisXYZ() const { return this->_AxisXYZ; }
dotSceneDirection dotSceneObjects::dotSceneOrientation::get_Direction() const { return this->_Direction; }
dotSceneQuaternion dotSceneObjects::dotSceneOrientation::get_Quaternion() const { return this->_Quaternion; }

void dotSceneObjects::dotSceneOrientation::set_AngleAxis(dotSceneAngleAxis value) { this->_AngleAxis = value; }
void dotSceneObjects::dotSceneOrientation::set_AxisXYZ(dotSceneAxisXYZ value) { this->_AxisXYZ = value; }
void dotSceneObjects::dotSceneOrientation::set_Direction(dotSceneDirection value) { this->_Direction = value; }
void dotSceneObjects::dotSceneOrientation::set_Quaternion(dotSceneQuaternion value) { this->_Quaternion = value; }

dotSceneAxisXYZ dotSceneObjects::dotSceneOrientation::convert(dotSceneQuaternion someQuaternion)
{
	dotSceneAxisXYZ someRotationMatrix = dotSceneAxisXYZ();

	someRotationMatrix.set_xAxisX(1 - (2 * ((someQuaternion.get_qy() * someQuaternion.get_qy()) + (someQuaternion.get_qz() * someQuaternion.get_qz()))));
	someRotationMatrix.set_xAxisY(2 * ((someQuaternion.get_qx() * someQuaternion.get_qy()) + (someQuaternion.get_qw() * someQuaternion.get_qz())));
	someRotationMatrix.set_xAxisZ(2 * ((someQuaternion.get_qx() * someQuaternion.get_qz()) - (someQuaternion.get_qw() * someQuaternion.get_qy())));
	someRotationMatrix.set_yAxisX(2 * ((someQuaternion.get_qx() * someQuaternion.get_qy()) - (someQuaternion.get_qw() * someQuaternion.get_qz())));
	someRotationMatrix.set_yAxisY(1 - (2 * ((someQuaternion.get_qz() * someQuaternion.get_qz()) + (someQuaternion.get_qx() * someQuaternion.get_qx()))));
	someRotationMatrix.set_yAxisZ(2 * ((someQuaternion.get_qy() * someQuaternion.get_qz()) + (someQuaternion.get_qw() + someQuaternion.get_qx())));
	someRotationMatrix.set_zAxisX(2 * ((someQuaternion.get_qx() * someQuaternion.get_qz()) + (someQuaternion.get_qw() * someQuaternion.get_qy())));
	someRotationMatrix.set_zAxisY(2 * ((someQuaternion.get_qy() * someQuaternion.get_qz()) - (someQuaternion.get_qw() + someQuaternion.get_qx())));
	someRotationMatrix.set_zAxisZ(1 - (2 * ((someQuaternion.get_qx() * someQuaternion.get_qx()) + (someQuaternion.get_qy() * someQuaternion.get_qy()))));

	return someRotationMatrix;
}

dotSceneQuaternion dotSceneObjects::dotSceneOrientation::convert(dotSceneAxisXYZ someMatrix)
{
	dotSceneQuaternion someQuaternion = dotSceneQuaternion();

	someQuaternion.set_qw((sqrt(someMatrix.get_xAxisX() + someMatrix.get_yAxisY() + someMatrix.get_zAxisZ())) / 2);
	someQuaternion.set_qx((someMatrix.get_zAxisY() - someMatrix.get_yAxisZ()) / (4 * someQuaternion.get_qw()));
	someQuaternion.set_qy((someMatrix.get_xAxisZ() - someMatrix.get_zAxisX()) / (4 * someQuaternion.get_qw()));
	someQuaternion.set_qz((someMatrix.get_yAxisX() - someMatrix.get_xAxisY()) / (4 * someQuaternion.get_qw()));

	return someQuaternion;
}

bool dotSceneObjects::dotSceneOrientation::IsValid() const
{
	if (!dotSceneObjects::dotSceneObject::IsValid()) return false;

	return true;
}

/// constructors & destructors
dotSceneObjects::dotSceneOrientation::dotSceneOrientation() : dotSceneObject(dotSceneEnums::orientation) { }
