#version 330 core

// Ouput data
in vec2 texCoords;
in vec4 fragColor;
out vec4 color;
uniform bool isTextured;
uniform sampler2D image;
uniform bool horizontal;
uniform float weight[7] = float[] (0.827027, 0.8945946, 0.1216216, 0.054054, 0.016216, 0.01,0.01);
uniform vec4 prevColor;
float Opacity=1.0;
void main()
{
    if(isTextured){
	vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
    vec3 result = texture(image, texCoords).rgb * weight[0]; // current fragment's contribution
    if(horizontal)
    {
        for(int i = 1; i < 7; ++i)
        {
            result += texture(image, texCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, texCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 7; ++i)
        {
            result += texture(image, texCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, texCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }

    color = vec4(result, Opacity);
  }
  else
  {
    color = fragColor;
  }
}
/*

void main()
{             
    vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
    vec3 result = texture(image, TexCoords).rgb * weight[0]; // current fragment's contribution
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    FragColor = vec4(result, 1.0);
}
*/