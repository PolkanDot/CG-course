void main()
{
    vec4 position = gl_Vertex;
    float x = position.x;
    float radius = (1.0 + sin(x)) * (1.0 + 0.9 * cos(8.0 * x)) * (1.0 + 0.1 * cos(24.0 * x)) * (0.5 + 0.05 * cos(140.0 * x));

    position.x = radius * cos(x) * 0.5;
    position.y = (radius * sin(x) * 0.5) - 0.5;

    gl_Position = gl_ModelViewProjectionMatrix * position;
}
