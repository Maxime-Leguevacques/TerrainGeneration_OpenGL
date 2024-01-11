#version 330 core
out vec4 FragColor;
in vec2 coord;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D dep;
in vec3 n_p;

void main()
{
    int m = 2;
    if(n_p.y > m)
    {
        FragColor = texture(tex1, coord);
    }
    else
    {
        float alpha = n_p.y / (m);
        FragColor = texture2D(tex1,coord)*alpha+texture2D(tex2,coord)*(1-alpha);
    }
}
