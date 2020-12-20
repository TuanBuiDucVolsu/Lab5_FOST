#include<glut.h>
#include<cmath>
//x - Расстояние между спутником и центром притяжения
float x = 1.2;
//y - координата спутника, начальное значение y=0
float y = 0;
//vx - составляющая скорости по Ох. В начальный момент времени vx= 0
double vx = 0;
//vy - составляющая скорости по Оу, В начальный момент времени vy = 1.2
double vy = 1.2;
//dt - шаг
double dt = 0.00005;
//t - Общее время
double t = dt;
//PI - число Пи
const double PI = 3.1415926535;
//m,k - Промежуточные переменные
double m, k;
double velo(double v, double z, double l, double ta) {
	m = z * z + l * l;
	k = sqrt(m);
	return (v - (z / (k * k * k) * ta));
}
//Вызывается при изменении размеров окна
void change_size(GLsizei w, GLsizei h) {
	GLdouble aspect_ratio;
	//Предотвращается деление на 0
	if (h == 0)
		h = 1;
	//Устанавливается поле просмотра с размерами окна
	glViewport(0, 0, w, h);
	//Обновляется система координат
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//С помощью плоскостей отсечения (левая, правая, нижняя,
	//верхняя, ближняя, дальняя) устанавливается объем отсечения
	aspect_ratio = (GLdouble)w / (GLdouble)h;
	if (w <= h)
		glOrtho(-40.0, 6.0, -23.0 / aspect_ratio, 23.0 / aspect_ratio, -1.0, 1.0);
	else
		glOrtho(-40.0 * aspect_ratio, 6.0 * aspect_ratio, -23.0, 23.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//Задается состояние визуализации
void initialise() {
	//Задается цвет очистки окна - черный
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
void render_scene() {
	//Очищается окно, используя текущий цвет очистки
	glClear(GL_COLOR_BUFFER_BIT);
	//В качестве текущего цвета рисования задаем красный
	//R G B
	glColor3f(1.0, 0.0, 0.0);
	//Рисуем координатную систему:
	//Рисуем ось Ох
	glBegin(GL_LINES);
	glVertex2f(-39.0, 0.0);
	glVertex2f(5.0, 0.0);
	glEnd();
	//Рисуем ось Оу
	glBegin(GL_LINES);
	glVertex2f(0.0, -22.0);
	glVertex2f(0.0, 22.0);
	glEnd();
	//Рисуем центр притяжения
	//Радиус центра = 1
	//Цвет закраски - зеленый
	glColor3f(0.0, 1.0, 0.0);
	double radian = 0.0;
	double xx, yy;
	glBegin(GL_POINTS);
	while (radian <= 2 * PI) {
		xx = cos(radian);
		yy = sin(radian);
		glVertex2d(xx, yy);
		radian += 0.05;
	}
	glEnd();
	//Задаем в качества цвета закраски синий
	glColor3f(0.0, 0.0, 1.0);
	//Рисуем траекторию первого спутника
	glBegin(GL_POINTS);
	while (t <= 70) {
		glVertex2d(x, y);
		vx = velo(vx, x, y, dt);
		vy = velo(vy, y, x, dt);
		x += vx * dt;
		y += vy * dt;
		t += dt;
	}
	glEnd();
	//Задаем начальные данные
	x = 1.25;
	y = 0;
	vx = 0;
	vy = 1.2;
	t = 0;
	//Рисуем траекторию второго спутника
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	while (t <= 200) {
		glVertex2d(x, y);
		vx = velo(vx, x, y, dt);
		vy = velo(vy, y, x, dt);
		x += vx * dt;
		y += vy * dt;
		t += dt;
	}
	glEnd();
	//Рисуем траекторию 3-го спутника
	x = 1.3;
	y = 0;
	vx = 0;
	vy = 1.2;
	t = 0;
	glColor3f(.5, .6, 1.0);
	glBegin(GL_POINTS);
	while (t <= 220) {
		glVertex2d(x, y);
		vx = velo(vx, x, y, dt);
		vy = velo(vy, y, x, dt);
		x += vx * dt;
		y += vy * dt;
		t += dt;
	}
	glEnd();
	//Очищаем очередь текущих команд
	glFlush();
}
//Точка входа основной программы
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//Задается размер окна
	glutInitWindowSize(640, 640);
	//Определяется позиции окна на рабочем столе
	glutInitWindowPosition(20, 20);
	//Создается окно с названием в кавычках
	glutCreateWindow("The movement of celestial bodies");
	//Дисплейная функция
	glutDisplayFunc(render_scene);
	//Функция перерисовки
	glutReshapeFunc(change_size);
	initialise();
	//Запускается оболочка GLUT
	glutMainLoop();
	return 0;
}