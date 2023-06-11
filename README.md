# 42KL-MiniRT
A simple raytracing engine.

todo: 

transformation pipeline
object space -> world space (model / transformation matrix)
world space -> view space (world to view matrix)
view space -> clip space (projection matrix)
clip space -> Normalized device coordinate space (perspective divide)
Normalized device coordinate space-> Screen space (map coordinates to pixels on screen)

get inverse of all the matrices -> transform the ray from view space -> world space

rays are transformed, not the objects