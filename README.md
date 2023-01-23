# Volleyball_Qt-Cpp
Simple game which is created in Qt/C++ plus physics engine Box2D.

## Screenshots
![Image](https://user-images.githubusercontent.com/28188300/177341023-179feb4d-566c-4e01-b1b5-041338f516f7.png)
![Image](https://user-images.githubusercontent.com/28188300/177341030-d1db8e3f-a384-4038-a2bd-e94f75e977cb.png)

### Installing
Get Box2D from: https://github.com/erincatto/box2d
Add Box2D's headers to include folder and Box2D lib to libs folder.
Create new function in b2_body.h
```
inline void b2Body::SetUserData(b2BodyUserData userData)
{
    m_userData = userData;
}
```
A step by step series  that tell you how to get a execute project.
Get it from GitHub
```
git@github.com:Przemekkkth/Volleyball_Qt-Cpp
```
Compile
```
qmake && make
```
## Adons
* [Qt](https://www.qt.io/) - Cross-Platform software for embedded & desktop
* [Box2D](https://github.com/erincatto/box2d) - Box2D
* [Yt](https://youtu.be/_w2k-Jtuf8k) - gameplay
