#define M_PI 3.1415926535897932384626433832795
#define WORLD_SIZE 1000.0

attribute vec4 vPosition;
varying vec4 fcolor;

uniform vec4 color;
uniform mat4 transform;
uniform mat4 projection;

void main()
{
	gl_Position = projection * transform * vPosition;
	
	fcolor = color;
}
