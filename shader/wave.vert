#version 330 core

layout(location = 0) in vec2 position;  // Координаты в пикселях
layout(location = 1) in vec2 texCoord;  // Текстурные координаты [0,1]

uniform vec2 u_resolution;  // Размер окна

out vec2 fragTexCoord;

void main() {
    // Преобразуем пиксельные координаты в clip-space [-1,1]
    vec2 clipPos = (position / u_resolution) * 2.0 - 1.0;
    
    // Инвертируем Y-ось (SFML → OpenGL)
    clipPos.y *= -1.0;
    
    gl_Position = vec4(clipPos, 0.0, 1.0);
    fragTexCoord = texCoord;
}