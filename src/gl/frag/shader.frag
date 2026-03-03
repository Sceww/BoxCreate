#version 330 core
out vec4 FragColor;

in vec3 aCol;
in vec2 texCoord;

uniform float time;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    // FragColor = vec4(texCoord, 0.0, 1.0);
    FragColor = mix (texture(texture1, (texCoord) * (sin(time*4)+1)/2), texture(texture2, texCoord+vec2(time,time/2)), (sin(time*2)+1)/2);
}