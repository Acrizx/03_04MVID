#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D screenTexture;
uniform vec2      textureSize;
uniform float     sigma;


float Gauss( float x, float sigm )
{
    if ( sigm <= 0.0 )
        return 0.0;
    return exp( -(x*x) / (2.0 * sigm) ) / (2.0 * 3.14157 * sigm);
}

void main()
{
    vec2 Centro     = uv.st * 0.5 + 0.5;
    vec4 texCol   = texture2D( screenTexture, Centro );
    vec4 gaussCol = vec4( texCol.rgb, 1.0 );
    vec2 step     = vec2(0.0,1.0) / textureSize;

    for ( int i = 1; i <= 32; ++ i )
    {
        float weight = Gauss( float(i) / 32.0, sigma * 0.5 );
        if ( weight < 1.0/255.0 )
            break;
        texCol    = texture2D( screenTexture, Centro + step * float(i) );
        gaussCol += vec4( texCol.rgb * weight, weight );
        texCol    = texture2D( screenTexture, Centro - step * float(i) );
        gaussCol += vec4( texCol.rgb * weight, weight );
    }

    step     = vec2(1.0,0.0) / textureSize;

    for ( int i = 1; i <= 32; ++ i )
    {
        float weight = Gauss( float(i) / 32.0, sigma * 0.5 );
        if ( weight < 1.0/255.0 )
            break;
        texCol    = texture2D( screenTexture, Centro + step * float(i) );
        gaussCol += vec4( texCol.rgb * weight, weight );
        texCol    = texture2D( screenTexture, Centro - step * float(i) );
        gaussCol += vec4( texCol.rgb * weight, weight );
    }

    gaussCol.rgb = clamp( gaussCol.rgb / gaussCol.w, 0.0, 1.0 );
    FragColor = vec4( gaussCol.rgb, 1.0 );
}