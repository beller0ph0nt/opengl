#version 120

void main(void) {
   gl_FragColor = vec4(gl_FragCoord.x / 640.0, gl_FragCoord.y / 480.0, 0.5, 1.0);
}
