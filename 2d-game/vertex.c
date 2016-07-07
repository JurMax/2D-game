
#version 330

uniform vec2 u_screenSize;
uniform vec2 u_screenOffset;

uniform float FXAA_SUBPIX_SHIFT = 1.0/4.0;

in vec2 vertexPos2D;
in vec4 vertexColor;
in vec2 vertexTexCoord;

out vec4 fragmentColor;
out vec2 fragmentTexCoord;
out vec4 posPos;

void main() {
    vec2 pos2D = vertexPos2D;
    pos2D += u_screenOffset;
    pos2D /= u_screenSize/2;
    
    gl_Position = vec4(pos2D.x, pos2D.y, 0.0, 1.0);
    
    fragmentColor = vertexColor;
    fragmentTexCoord = vertexTexCoord;
    
    vec2 rcpFrame = vec2(1.0/u_screenSize.x, 1.0/u_screenSize.y);
    posPos.xy = vertexTexCoord.xy;
    posPos.zw = vertexTexCoord.xy - (rcpFrame * (0.5 + FXAA_SUBPIX_SHIFT));
}