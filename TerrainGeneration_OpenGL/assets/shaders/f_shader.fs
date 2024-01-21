#version 460 core
out vec4 FragColor;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D dep;
in vec2 coord;
in vec3 n_p;
in float TSH;
flat in int mode;
in float highestY;



void main()
{
    vec2 uv = coord*10;

    if (mode == 0) {
        float alpha = n_p.y / highestY;
        float weightTex1 = 0.7;
        vec4 w1 = texture(tex1, uv) * alpha;
        vec4 w2 = texture(tex2, uv) * (1 - alpha);
        FragColor = w1 + w2;
    }
    else if (mode == 1) {

        if (n_p.y > TSH) {
            FragColor = texture(tex1, uv);
        }
        else {
            FragColor = texture(tex2, uv);
        }
    }
    //FragColor = vec4(coord, 0, 1);
}