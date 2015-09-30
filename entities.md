# We need the following types of entities: #

## Type: Robot ##

  * **Absolutposition (Odete):** str: typeid = "odete", vec2 position, quat roration

  * **PTU:** str: typeid = "albertHead", vec2 ptu -`> pan, tilt

  * **AMTEC-Arm:** str: typeid = "albertArm", vec3 position, quat rotation, double joint1, ... double joint7 (http://i61p109.ira.uka.de/twiki/bin/view/IlcasProjects/BeispielpositionenArm)

  * **BARRET-Hand:** str: typeid = "albertHand", double finger1-angle, double finger2-angle, double finger3-angle, double spread-angle


## Type: Object ##
  * str: typeid = "movableObject"
  * string: ObjType
  * vec3 position, quat rotation


## Type: Human ##

## Type: Ellipsis ##

  * maybe geometric objects in general?

## Type: Line: ##
  * str: typeid = "line"
  * vec3 startPoint, vec3 endPoint
  * str: color