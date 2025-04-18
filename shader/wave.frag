#version 330 core

uniform vec2 u_points[300];  // Массив точек (максимум 10)
uniform int u_points_count; 
uniform float u_time;    // Время для анимации
uniform vec2 u_resolution;

out vec4 fragColor;

void main() {
    // Нормализованные координаты пикселя [0,1] (с инверсией Y)
    vec2 uv = vec2(gl_FragCoord.x / u_resolution.x,  gl_FragCoord.y / u_resolution.y);
    
   float total_wave = 0.0;
    
    // Суммируем волны от всех точек
    for (int i = 0; i < u_points_count; i++) {
        float dist = distance(uv, u_points[i]);
        total_wave += sin(dist * 20.0 - u_time * 1.0) * exp(-dist * 5.0);
    }
    
    // Нормализуем и преобразуем в цвет
    fragColor = vec4(0.0, 0.3, 1.0, 1.0) * total_wave;
}