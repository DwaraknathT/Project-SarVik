#version 330 
layout (location = 0) in vec3 vertPos;
layout (location = 2) in vec2 inTexCoord;
layout(location = 1) in vec4 frag;
out vec4 fragColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 texCoords;
void main(){
	texCoords = inTexCoord;
	gl_Position = projection*view*model*vec4(vertPos,1);
	fragColor = frag;
}
