#version 460 core
out vec4 FragColor;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D dep;
in vec2 coord;
in vec3 n_p;
in float TSH;
flat in int mode;



void main()
{
    vec2 uv = coord*10;

    if (mode == 0) {
        if(n_p.y > TSH) {
            FragColor = texture(tex1, uv);
        }
        else {
            float alpha = n_p.y / TSH;
            float weightTex1 = 0.7;
            FragColor = texture(tex1, uv) * (alpha * weightTex1) + texture(tex2, uv) * (1.0 - alpha * weightTex1);
        }
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