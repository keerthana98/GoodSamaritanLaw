#include<Windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

void display();
void dialogB1();
void reshape(int, int);
void timer1(int);
void timer(int);
void key(unsigned char, int, int);
float xc, yc, angle;
float x = 2000;
float new_ypos = 1000, x_pos = 0;
int f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0, f6 = 0, f7 = 0,f8=0,f9=0,lscnt=0;
int new_x = 200;
int dialogBCnt = 0, lawCnt = 0, dialogBCnt1=0;
float x_position = 150.0;
void *currentfont;
void setFont(void *font)
{
	currentfont = font;
}
void drawstring(float x, float y, float z, char *string)
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutBitmapCharacter(currentfont, *c);
	}
}
void backgroundCol()
{

	glPushMatrix();

	//left sky
	glBegin(GL_QUADS);
	glColor3f(0, 0.498039, 1);
	glVertex2i(0, 2200);
	glVertex2i(2000, 2200);
	glVertex2i(2200, 3400);
	glVertex2i(0, 3400);
	glEnd();

	//right sky
	glBegin(GL_QUADS);
	glColor3f(0, 0.498039, 1);
	glVertex2i(2900, 2200);
	glVertex2i(4600, 2200);
	glVertex2i(4600, 3400);
	glVertex2i(2600, 3400);
	glEnd();

	//road
	glBegin(GL_POLYGON);
	glColor3f(0.658824, 0.65882, 0.658824);
	glVertex2i(0, 2200);//a
	glVertex2i(4600, 2200);//i
	glVertex2i(4600, 1400);//h
	glVertex2i(0, 1400);//b
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.658824, 0.65882, 0.658824);
	glVertex2i(2000, 1400);//d
	glVertex2i(1800, 0);//e
	glVertex2i(3200, 0);//f
	glVertex2i(2900, 1400);//g
	glVertex2i(2900, 2200);//j
	glVertex2i(2600, 3400);//k
	glVertex2i(2200, 3400);//l
	glVertex2i(2000, 2200);//c
	glEnd();

	//grass
	glBegin(GL_POLYGON);
	glColor3f(0, 0.5, 0);
	glVertex2i(0, 0);//a
	glVertex2i(1800, 0);//e
	glVertex2i(2000, 1400);//d
	glVertex2i(0, 1400);//b
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0.5, 0);
	glVertex2i(3200, 0);//f
	glVertex2i(2900, 1400);//g
	glVertex2i(4600, 1400);//h
	glVertex2i(4600, 0);//b
	glEnd();
	glPopMatrix();
}
void person()
{
	float angle;
	int xc = 3100, yc = new_ypos + 1700;
	glColor3f(1, 0, 0);

	glPushMatrix();

	//face
	glBegin(GL_POLYGON);
	glColor3f(0.91, 0.76, 0.65);
	for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
		glVertex2f((xc + (100 * cos(angle))), (yc + (100 * sin(angle))));
	glEnd();


	//neck
	glBegin(GL_POLYGON);//IK
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3120, new_ypos + 1605);//I
	glVertex2i(3120, new_ypos + 1560);//K
	glVertex2i(3080, new_ypos + 1560);//J
	glVertex2i(3080, new_ypos + 1605);//H
	glEnd();

	//body
	glBegin(GL_POLYGON);
	glColor3f(0,0, 0.61);
	glVertex2i(3120, new_ypos + 1560);//K
	glVertex2i(3200, new_ypos + 1540);//L
	glVertex2i(3180, new_ypos + 1400);//O
	glVertex2i(3020, new_ypos + 1400);//C'
	glVertex2i(3000, new_ypos + 1540);//F'
	glVertex2i(3080, new_ypos + 1560);//J
	glEnd();

	//body-lower
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex2i(3180, new_ypos + 1400);//O
	glVertex2i(3200, new_ypos + 1280);//R
	glVertex2i(3160, new_ypos + 1280);//V
	glVertex2i(3100, new_ypos + 1300);//W
	glVertex2i(3060, new_ypos + 1280);//X
	glVertex2i(3000, new_ypos + 1280);//B'
	glVertex2i(3020, new_ypos + 1400);//C'
	glEnd();

	//leg - right
	glBegin(GL_POLYGON);
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3200, new_ypos + 1280);//R
	glVertex2i(3180, new_ypos + 1160);//S
	glVertex2i(3100, new_ypos + 1160);//T
	glVertex2i(3150, new_ypos + 1200);//U
	glVertex2i(3150, new_ypos + 1280);//V
	glEnd();

	//leg-left
	glBegin(GL_POLYGON);
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3060, new_ypos + 1280);//X
	glVertex2i(3040, new_ypos + 1160);//Y
	glVertex2i(2960, new_ypos + 1160);//Z
	glVertex2i(3000, new_ypos + 1200);//A'
	glVertex2i(3010, new_ypos + 1280);//B'
	glEnd();

	//-----HAND-RIGHT -----
	glBegin(GL_LINES);//outer
	glVertex2i(3200, new_ypos + 1540);//L
	glVertex2i(3260, new_ypos + 1460);//M
	glVertex2i(3260, new_ypos + 1460);//M
	glVertex2i(3180, new_ypos + 1420);//N
	glEnd();

	glBegin(GL_LINES);//inner
	glVertex2i(3200, new_ypos + 1500);//P
	glVertex2i(3220, new_ypos + 1480);//J'
	glVertex2i(3220, new_ypos + 1480);//J'
	glVertex2i(3180, new_ypos + 1460);//Q
	glEnd();

	glBegin(GL_POLYGON);//to color hand top
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3200, new_ypos + 1500);//P
	glVertex2i(3200, new_ypos + 1540);//L
	glVertex2i(3260, new_ypos + 1460);//M
	glVertex2i(3230, new_ypos + 1480);//J'
	glEnd();

	glBegin(GL_POLYGON);//to color hand lower
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3230, new_ypos + 1480);//J'
	glVertex2i(3180, new_ypos + 1450);//Q
	glVertex2i(3180, new_ypos + 1420);//N
	glVertex2i(3260, new_ypos + 1460);//M
	glEnd();

	//----HAND-LEFT-----
	glBegin(GL_LINES);//outer
	glVertex2i(3000, new_ypos + 1540);//F'
	glVertex2i(2940, new_ypos + 1460);//E'
	glVertex2i(2940, new_ypos + 1460);//E'
	glVertex2i(3020, new_ypos + 1420);//D'
	glEnd();

	glBegin(GL_LINES);//inner
	glVertex2i(3000, new_ypos + 1500);//G'
	glVertex2i(2980, new_ypos + 1480);//I'
	glVertex2i(2980, new_ypos + 1480);//I'
	glVertex2i(3020, new_ypos + 1460);//H'
	glEnd();

	glBegin(GL_POLYGON);//to color hand top
	glVertex2i(3000, new_ypos + 1540);//F'
	glVertex2i(2940, new_ypos + 1460);//E'
	glVertex2i(2980, new_ypos + 1480);//I'
	glVertex2i(3000, new_ypos + 1500);//G'
	glEnd();

	glBegin(GL_POLYGON);//to color hand lower
	glVertex2i(2975, new_ypos + 1480);//I'
	glVertex2i(3020, new_ypos + 1460);//H'
	glVertex2i(3020, new_ypos + 1420);//D'
	glVertex2i(2940, new_ypos + 1460);//E'

	glEnd();


	glPopMatrix();

}
void sam()
{
	float angle;
	int xc = x + 2500, yc = new_ypos + 1700;
	glColor3f(1, 0, 0);

	glPushMatrix();

	//face
	glBegin(GL_POLYGON);
	glColor3f(0.91, 0.76, 0.65);
	for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
		glVertex2f((xc + (100 * cos(angle))), (yc + (100 * sin(angle))));
	glEnd();

	//neck
	glBegin(GL_POLYGON);//IK
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(x + 2520, new_ypos + 1605);//I
	glVertex2i(x + 2520, new_ypos + 1560);//K
	glVertex2i(x + 2480, new_ypos + 1560);//J
	glVertex2i(x + 2480, new_ypos + 1605);//H
	glEnd();

	//body-upper
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.61);
	glVertex2i(x + 2520, new_ypos + 1560);//K
	glVertex2i(x + 2600, new_ypos + 1540);//L
	glVertex2i(x + 2580, new_ypos + 1400);//O
	glVertex2i(x + 2420, new_ypos + 1400);//C'
	glVertex2i(x + 2400, new_ypos + 1540);//F'
	glVertex2i(x + 2480, new_ypos + 1560);//J
	glEnd();

	//body-lower
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex2i(x + 2580, new_ypos + 1400);//O
	glVertex2i(x + 2600, new_ypos + 1280);//R
	glVertex2i(x + 2560, new_ypos + 1280);//V
	glVertex2i(x + 2500, new_ypos + 1300);//W
	glVertex2i(x + 2460, new_ypos + 1280);//X
	glVertex2i(x + 2400, new_ypos + 1280);//B'
	glVertex2i(x + 2420, new_ypos + 1400);//C'
	glEnd();

	//leg - right
	glBegin(GL_POLYGON);
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(x + 2600, new_ypos + 1280);//R
	glVertex2i(x + 2580, new_ypos + 1160);//S
	glVertex2i(x + 2500, new_ypos + 1160);//T
	glVertex2i(x + 2550, new_ypos + 1200);//U
	glVertex2i(x + 2550, new_ypos + 1280);//V
	glEnd();

	//leg-left
	glBegin(GL_POLYGON);
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(x + 2460, new_ypos + 1280);//X
	glVertex2i(x + 2440, new_ypos + 1160);//Y
	glVertex2i(x + 2360, new_ypos + 1160);//Z
	glVertex2i(x + 2400, new_ypos + 1200);//A'
	glVertex2i(x + 2410, new_ypos + 1280);//B'
	glEnd();

	//-----HAND-RIGHT -----
	glBegin(GL_LINES);//outer
	glVertex2i(x + 2600, new_ypos + 1540);//L
	glVertex2i(x + 2660, new_ypos + 1460);//M
	glVertex2i(x + 2660, new_ypos + 1460);//M
	glVertex2i(x + 2580, new_ypos + 1420);//N
	glEnd();

	glBegin(GL_LINES);//inner
	glVertex2i(x + 2660, new_ypos + 1500);//P
	glVertex2i(x + 2620, new_ypos + 1480);//J'
	glVertex2i(x + 2620, new_ypos + 1480);//J'
	glVertex2i(x + 2580, new_ypos + 1460);//Q
	glEnd();

	glBegin(GL_POLYGON);//to color hand top
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(x + 2600, new_ypos + 1500);//P
	glVertex2i(x + 2600, new_ypos + 1540);//L
	glVertex2i(x + 2660, new_ypos + 1460);//M
	glVertex2i(x + 2630, new_ypos + 1480);//J'
	glEnd();

	glBegin(GL_POLYGON);//to color hand lower
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(x + 2630, new_ypos + 1480);//J'
	glVertex2i(x + 2580, new_ypos + 1450);//Q
	glVertex2i(x + 2580, new_ypos + 1420);//N
	glVertex2i(x + 2660, new_ypos + 1460);//M
	glEnd();

	//----HAND-LEFT-----
	glBegin(GL_LINES);//outer
	glVertex2i(x + 2400, new_ypos + 1540);//F'
	glVertex2i(x + 2340, new_ypos + 1460);//E'
	glVertex2i(x + 2340, new_ypos + 1460);//E'
	glVertex2i(x + 2420, new_ypos + 1420);//D'
	glEnd();

	glBegin(GL_LINES);//inner
	glVertex2i(x + 2400, new_ypos + 1500);//G'
	glVertex2i(x + 2380, new_ypos + 1480);//I'
	glVertex2i(x + 2380, new_ypos + 1480);//I'
	glVertex2i(x + 2420, new_ypos + 1460);//H'
	glEnd();

	glBegin(GL_POLYGON);//to color hand top
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(x + 2400, new_ypos + 1540);//F'
	glVertex2i(x + 2340, new_ypos + 1460);//E'
	glVertex2i(x + 2380, new_ypos + 1480);//I'
	glVertex2i(x + 2400, new_ypos + 1500);//G'
	glEnd();

	glBegin(GL_POLYGON);//to color hand lower
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(x + 2375, new_ypos + 1480);//I'
	glVertex2i(x + 2420, new_ypos + 1460);//H'
	glVertex2i(x + 2420, new_ypos + 1420);//D'
	glVertex2i(x + 2340, new_ypos + 1460);//E'
	glEnd();
	glPopMatrix();

}
void person1()
{
	float angle;
	//new_ypos = 696;
	int xc = 3100, yc = new_ypos + 1700;
	glColor3f(1, 0, 0);
	glTranslatef(3250.0, 1800.0, 0.0);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-3250.0, -1800.0, 0.0);
	glPushMatrix();

	//face
	glBegin(GL_POLYGON);
	glColor3f(0.91, 0.76, 0.65);
	for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
		glVertex2f((xc + (100 * cos(angle))), (yc + (100 * sin(angle))));
	glEnd();

	//neck
	glBegin(GL_POLYGON);//IK
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3120, new_ypos + 1605);//I
	glVertex2i(3120, new_ypos + 1560);//K
	glVertex2i(3080, new_ypos + 1560);//J
	glVertex2i(3080, new_ypos + 1605);//H
	glEnd();

	//body
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.61);
	glVertex2i(3120, new_ypos + 1560);//K
	glVertex2i(3200, new_ypos + 1540);//L
	glVertex2i(3180, new_ypos + 1400);//O
	glVertex2i(3020, new_ypos + 1400);//C'
	glVertex2i(3000, new_ypos + 1540);//F'
	glVertex2i(3080, new_ypos + 1560);//J
	glEnd();

	//body-lower
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex2i(3180, new_ypos + 1400);//O
	glVertex2i(3200, new_ypos + 1280);//R
	glVertex2i(3160, new_ypos + 1280);//V
	glVertex2i(3100, new_ypos + 1300);//W
	glVertex2i(3060, new_ypos + 1280);//X
	glVertex2i(3000, new_ypos + 1280);//B'
	glVertex2i(3020, new_ypos + 1400);//C'
	glEnd();

	//leg - right
	glBegin(GL_POLYGON);
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3200, new_ypos + 1280);//R
	glVertex2i(3180, new_ypos + 1160);//S
	glVertex2i(3100, new_ypos + 1160);//T
	glVertex2i(3150, new_ypos + 1200);//U
	glVertex2i(3150, new_ypos + 1280);//V
	glEnd();

	//leg-left
	glBegin(GL_POLYGON);
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3060, new_ypos + 1280);//X
	glVertex2i(3040, new_ypos + 1160);//Y
	glVertex2i(2960, new_ypos + 1160);//Z
	glVertex2i(3000, new_ypos + 1200);//A'
	glVertex2i(3010, new_ypos + 1280);//B'
	glEnd();

	//-----HAND-RIGHT -----
	glBegin(GL_LINES);//outer
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3200, new_ypos + 1540);//L
	glVertex2i(3260, new_ypos + 1460);//M
	glVertex2i(3260, new_ypos + 1460);//M
	glVertex2i(3180, new_ypos + 1420);//N
	glEnd();

	glBegin(GL_LINES);//inner
	glVertex2i(3200, new_ypos + 1500);//P
	glVertex2i(3220, new_ypos + 1480);//J'
	glVertex2i(3220, new_ypos + 1480);//J'
	glVertex2i(3180, new_ypos + 1460);//Q
	glEnd();

	glBegin(GL_POLYGON);//to color hand top
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3200, new_ypos + 1500);//P
	glVertex2i(3200, new_ypos + 1540);//L
	glVertex2i(3260, new_ypos + 1460);//M
	glVertex2i(3230, new_ypos + 1480);//J'
	glEnd();

	glBegin(GL_POLYGON);//to color hand lower
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3230, new_ypos + 1480);//J'
	glVertex2i(3180, new_ypos + 1450);//Q
	glVertex2i(3180, new_ypos + 1420);//N
	glVertex2i(3260, new_ypos + 1460);//M
	glEnd();

	//----HAND-LEFT-----
	glBegin(GL_LINES);//outer
	glVertex2i(3000, new_ypos + 1540);//F'
	glVertex2i(2940, new_ypos + 1460);//E'
	glVertex2i(2940, new_ypos + 1460);//E'
	glVertex2i(3020, new_ypos + 1420);//D'
	glEnd();

	glBegin(GL_LINES);//inner
	glVertex2i(3000, new_ypos + 1500);//G'
	glVertex2i(2980, new_ypos + 1480);//I'
	glVertex2i(2980, new_ypos + 1480);//I'
	glVertex2i(3020, new_ypos + 1460);//H'
	glEnd();

	glBegin(GL_POLYGON);//to color hand top
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(3000, new_ypos + 1540);//F'
	glVertex2i(2940, new_ypos + 1460);//E'
	glVertex2i(2980, new_ypos + 1480);//I'
	glVertex2i(3000, new_ypos + 1500);//G'
	glEnd();

	glBegin(GL_POLYGON);//to color hand lower
	glColor3f(0.91, 0.76, 0.65);
	glVertex2i(2975, new_ypos + 1480);//I'
	glVertex2i(3020, new_ypos + 1460);//H'
	glVertex2i(3020, new_ypos + 1420);//D'
	glVertex2i(2940, new_ypos + 1460);//E'

	glEnd();


	glPopMatrix();

}

void road()
{
	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, 2200);//a
	glVertex2i(2000, 2200);//c
	glVertex2i(2000, 2200);//c
	glVertex2i(2200, 3400);//l

	glVertex2i(2600, 3400);//k
	glVertex2i(2900, 2200);//j
	glVertex2i(2900, 2200);//j
	glVertex2i(4600, 2200);//i

	glVertex2i(4600, 1400);//h
	glVertex2i(2900, 1400);//g
	glVertex2i(2900, 1400);//g
	glVertex2i(3200, 0);//f

	glVertex2i(1800, 0);//e
	glVertex2i(2000, 1400);//d
	glVertex2i(2000, 1400);//d
	glVertex2i(0, 1400);//b

	glEnd();
	glPopMatrix();
}
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
}
void key(unsigned char key, int x, int y)
{
	if (key == 'r')
	{
		glPushMatrix();
		xc = 0;
		yc = 0;
		angle=0;
		x = 2000;
		new_ypos = 1000;
		x_pos = 0;
		lscnt = 0;
		new_x = 200;
		dialogBCnt = 0;
		lawCnt = 0;
		dialogBCnt1 = 0;
		x_position = 150.0;
		f1 = 0;
		f2 = 0;
		f3 = 0;
		f4 = 0;
		f5 = 0;
		f6 = 0;
		f7 = 0;
		f8 = 0;
		f9 = 0;
		glPopMatrix();
		printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", f1, f2, f3, f4, f5, f6, f7,f8,f9);
		
		glutPostRedisplay();
	}
	else if (key == 'x')
	{
		exit(0);
	}
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(4600, 3400);
	glutCreateWindow("win");
	glutTimerFunc(1000, timer, 0);
	glutTimerFunc(1000, timer1, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutReshapeFunc(reshape);
	init();

	glutMainLoop();

}

void bus()
{
	glBegin(GL_QUADS);//ABCD
	glColor3f(0.55, 0.09, 0.08);
	glVertex2f(x_position, 1800);//A
	glVertex2f(x_position + 1250, 1800);//B
	glVertex2f(x_position + 1250, 2800);//C
	glVertex2f(x_position, 2800);//D
	glEnd();


	glBegin(GL_POLYGON);//BEFG
	glColor3f(0.59, 0.41, 0.31);
	glVertex2i(x_position + 1250, 1800);//B
	glVertex2i(x_position + 1450, 1800);//E
	glVertex2i(x_position + 1450, 2300);//F
	glVertex2i(x_position + 1290, 2300);//H
	glVertex2i(x_position + 1290, 2500);//I
	glVertex2i(x_position + 1250, 2500);//J
	glEnd();

	int xc = x_position + 350, yc = 1800;//wheel 1
	float angle;
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
		glVertex2f((xc + (100 * cos(angle))), (yc + (100 * sin(angle))));
	glEnd();

	glColor3f(0.329412, 0.329412, 0.329412);//inner circle of wheel
	glBegin(GL_POLYGON);
	for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
		glVertex2f((xc + (60 * cos(angle))), (yc + (60 * sin(angle))));
	glEnd();

	xc = x_position + 950;
	yc = 1800;//wheel 2
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
		glVertex2f((xc + (100 * cos(angle))), (yc + (100 * sin(angle))));
	glEnd();
	glColor3f(0.329412, 0.329412, 0.329412);//inner circle of wheel
	glBegin(GL_POLYGON);
	for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
		glVertex2f((xc + (60 * cos(angle))), (yc + (60 * sin(angle))));
	glEnd();

}
void dialogB()
{
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	xc = 3600;
	yc = 2600;

	for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
		glVertex2f((xc + (300 * cos(angle))), (yc + (250 * sin(angle))));
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2i(3800, 2480);
	glVertex2i(4000, 2500);
	glVertex2i(3880, 2680);
	glEnd();
	glColor3f(0, 0, 0);


	char txt[] = { 'I','f',' ','I',' ','C','a','l','l',' ','t','h','e',' ',
				   'A','m','b','u','l','a','n','c','e',',',
					't','h','e',' ','p','o','l','i','c','e',' ',
					'm','i','g','h','t',' ','s','u','s','p','e','c','t',' ',
					 'm','e' };
	glRasterPos2i(3350, 2700);
	for (int i = 0; i < 51; i++)
	{
		if (i == 14)
			glRasterPos2i(3350, 2630);
		if (i == 34)
			glRasterPos2i(3350, 2560);
		if (i == 35)
			glRasterPos2i(3350, 2550);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, txt[i]);
	}
	f4 = 1;
}
void dialogB1()
{
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	xc = 3600;
	yc = 2600;

	for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
		glVertex2f((xc + (300 * cos(angle))), (yc + (250 * sin(angle))));
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2i(3800, 2480);
	glVertex2i(4000, 2500);
	glVertex2i(3880, 2680);
	glEnd();
	glColor3f(0, 0, 0);


	char txt[] = {'I','l','l',' ','C','a','l','l',' ','t','h','e',' ',
				   'A','m','b','u','l','a','n','c','e',',','a','s',
					' ','i',' ','a','m',' ','p','r','o','t','e','c','t','e','d',' ','u','n','d','e','r',' ','t','h','e',' ','l','a','w' };
	glRasterPos2i(3350, 2700);
	for (int i = 0; i < 54; i++)
	{
		if (i == 13)
			glRasterPos2i(3350, 2630);
		if (i == 27)
			glRasterPos2i(3350, 2560);
		if (i == 47)
			glRasterPos2i(3350, 2490);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, txt[i]);
	}
	f4 = 1;
}
void nextScene()
{
	//printf("next scene");
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(1, 1, 1, 1);

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glClearColor(0, 0, 0, 0);/*background for cover page*/
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 1, 0);
	drawstring(400.0, 2800.0, 0.0, "THE GOOD SAMARITAN LAW STATES THAT");
	glColor3f(1, 0, 0);
	drawstring(400.0, 2600.0, 0.0, "NO PERSON CAN BE BOOKED AS ACCUSED WHILE HE/SHE TRIES TO SAVE ACCIDENT VICTIMS");
	glColor3f(0, 0, 1);
	drawstring(400.0, 2400.0, 0.0, "WHICH WAS PUT IN FORCE BY THE SUPREME COURT ON MARCH 30TH,2016 ");
	
	glColor3f(0, 1, 0);
	drawstring(400.0, 2200.0, 0.0, "YOUR RIGHTS AS A GOOD SAMARITAN ");

	glColor3f(1, 1, 0);
	drawstring(400.0, 2000.0, 0.0, "1)THE GOOD SAMARITAN SHALL NOT FACE ANY CIVIL AND CRIMINAL LIABILITY");
	glColor3f(1, 0, 1);
	drawstring(400.0, 1800.0, 0.0, "ARISING OUT OF HELPING CRASH VICTIM.");
	glColor3f(0, 1, 0);
	drawstring(400.0, 1600.0, 0.0, "2)SHALL NOT BE COMPELLED TO REVEAL HIS NAME ");
	glColor3f(0, 1, 1);
	drawstring(400.0, 1400.0, 0.0, "AND PERSONAL DETAILS ON PHONE OR IN PERSON.");
	glColor3f(1, 0, 0);
	drawstring(400.0, 1200.0, 0.0, "3)DISCIPLINARY ACTION SHALL BE INITIATED BY THE GOVERNMENT CONCERNED");
	glColor3f(0, 1, 0);
	drawstring(400.0, 1000.0, 0.0, "AGAINST PUBLIC OFFICIALS WHO COERCE OR INITIMIDATE A BYSTANDER.");
	
	glFlush();
}
void finalScene()
{
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glClearColor(0, 0, 0, 0);/*background for cover page*/
	glClear(GL_COLOR_BUFFER_BIT);
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	drawstring(800.0, 2800.0, 0.0, "SO NEXT TIME THERE IS AN ACCIDENT");
	glColor3f(0.7, 0, 1);
	drawstring(900, 2600, 0.0, "PLEASE DO HELP THE VICTIM");
	glColor3f(1, 0.5, 0);
	drawstring(1000, 2400, 0.0, "AND LEAVE THE REST TO THE LAW");

	glColor3f(1, 0.5, 0);
	drawstring(1200, 1000, 0.0, "Press 'r' to replay or 'x' to exit");
	
	glFlush();
	
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();

	backgroundCol();
	bus();
	//road();
	if (f1 == 0)
		person();
	if (f1 == 1)
	{
		glPushMatrix();
		person1();
		f2 = 1;
		glPopMatrix();

		glPushMatrix();
		sam();
		glPopMatrix();
	}

	if (f3 == 1)
	{
		glPushMatrix();
		dialogB();
		glPopMatrix();
	}
	if (f4 == 1)
	{
		glPushMatrix();
		sam();
		glPopMatrix();
	}
	if (f5 == 1)
	{
		glPushMatrix();
		sam();
		glPopMatrix();
	}
	if (f6 == 1)
	{
		glPushMatrix();
		nextScene();
		glPopMatrix();
	}
	if (f7 == 1)
	{
		
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		
		backgroundCol();
		bus();

		if (f1 == 1)
		{
			glPushMatrix();
			person1();
			f2 = 1;
			glPopMatrix();

			glPushMatrix();
			sam();
			glPopMatrix();
		}
		if (f3 == 1)
		{
			glPushMatrix();
			dialogB1();
			glPopMatrix();
		}
		
		glFlush();
	}
	if (f8 == 1)
	{
		glPushMatrix();
		glBegin(GL_POLYGON);//a
		glColor3f(1, 1, 1);
		glVertex2f(new_x-200, 1600);
		glVertex2f(new_x+1000,1600);
		glVertex2f(new_x + 1000,2500);
		glVertex2f(new_x-200, 2500);
		glEnd();

		glBegin(GL_POLYGON);//b
		glColor3f(1, 1, 1);
		glVertex2f(new_x + 1000, 2100);
		glVertex2f(new_x + 1200, 2000);
		glVertex2f(new_x + 1200, 1600);
		glVertex2f(new_x + 1000, 1600);
		glEnd();

		glBegin(GL_TRIANGLES);//window-blue
		glColor3f(0.196078, 0.6, 0.8);
		glVertex2f(new_x+1000,2040);
		glVertex2f(new_x + 1000, 2400);
		glVertex2f(new_x + 1100, 2040);
		glEnd();

		glBegin(GL_POLYGON);//red cross
		glColor3f(1, 0, 0);

		glVertex2f(new_x + 400, 2300);//1
		glVertex2f(new_x + 500, 2300);//2
		
		glVertex2f(new_x + 500, 2000);//7
		glVertex2f(new_x + 400, 2000);//8
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(new_x + 300, 2100);//10
		glVertex2f(new_x + 300, 2200);//11
		glVertex2f(new_x + 600, 2200);//4
        glVertex2f(new_x + 600, 2100);//5
		glEnd();

		xc = new_x+100;
		yc = 1600;
		glBegin(GL_POLYGON);
		glColor3f(0, 0, 0);
		for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
			glVertex2f((xc + (100 * cos(angle))), (yc + (100 * sin(angle))));
		glEnd();
		glColor3f(0.329412, 0.329412, 0.329412);//inner circle of wheel
		glBegin(GL_POLYGON);
		for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
			glVertex2f((xc + (60 * cos(angle))), (yc + (60 * sin(angle))));
		glEnd();

		xc = new_x+700;
		yc = 1600;
		glBegin(GL_POLYGON);
		glColor3f(0, 0, 0);
		for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
			glVertex2f((xc + (100 * cos(angle))), (yc + (100 * sin(angle))));
		glEnd();
		glColor3f(0.329412, 0.329412, 0.329412);//inner circle of wheel
		glBegin(GL_POLYGON);
		for (angle = 0.0; angle <= (2 * 3.142); angle += 0.0001)
			glVertex2f((xc + (60 * cos(angle))), (yc + (60 * sin(angle))));
		glEnd();
		glPopMatrix();
		
	}
	if (f9 == 1)
	{
		glPushMatrix();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0,0, 0, 1);
		finalScene();
		glPopMatrix();
		f1 = 0;
		f2 = 0;
		f3 = 0;
		f4 = 0;
		
		printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d", f1, f2, f3, f4, f5, f6, f7);
		
	}


	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 4600, 0, 3400);
	glMatrixMode(GL_MODELVIEW);
}
void timer(int a)
{
	glutPostRedisplay();

	glutTimerFunc(1000 / 60, timer, 0);

	if (x_position < 1550) {
		x_position += 40.8;
		printf("x:%lf\t", x_position);
	}
	if (new_ypos > 700)
	{
		new_ypos -= 8;
		printf("%lf\t", new_ypos);
	}
	if (new_ypos < 696)
		f1 = 0;
	if (new_ypos == 696)
		f1 = 1;
	if (f2 == 1)
	{
		if (x > 1600)
			x -= 8;
		if (x <= 1600)
			f3 = 1;
	}
	if (f4 == 1)
	{
		dialogBCnt += 2;
		if (dialogBCnt > 30)
			f3 = 0;
		if (dialogBCnt == 30)
			f5 = 1;
	}
	if (f5 == 1)
	{
		f4 = 0;
		if (x < 4500)
			x += 40;
		if (x >= 4500)
			f6 = 1;
	}
	if (f6 == 1)
	{
		lawCnt += 1;
		if (lawCnt > 300)
			f5 = 0;
		if (lawCnt == 300)
			f7 = 1;
	}
}
void timer1(int a)
{
	glutPostRedisplay();

	glutTimerFunc(1000 / 30, timer1, 0);

	if (f7 == 1)
	{
		if (x_position < 1550) {
			x_position += 50.8;
			printf("x:%lf\t", x_position);
		}
		if (new_ypos > 700)
		{
			new_ypos -= 8;
			printf("%lf\t", new_ypos);
		}
		if (new_ypos < 696)
			f1 = 0;
		if (new_ypos == 696)
			f1 = 1;
		if (f2 == 1)
		{
			if (x > 1600)
				x -= 40;
			if (x <= 1600)
				f3 = 1;
		}
		if (f4 == 1)
		{
			dialogBCnt1 += 1;
			if (dialogBCnt1 > 50)
				f3 = 0;
			if (dialogBCnt1 == 50)
				f8 = 1;
		}
		if (f5 == 1)
		{
			f4 = 0;
			if (x < 4500)
				x += 40;
			if (x >= 4500)
				f6 = 1;
		}
		if (f6 == 1)
		{
			lawCnt += 1;
			if (lawCnt > 50)
				f5 = 0;
			if (lawCnt == 50) {
				f7 = 1;
				f1 = 0;
				f2 = 0;
				f3 = 0;
				f4 = 0;
				f5 = 0;
				f6 = 0;
				new_ypos = 1000;
				x_pos = 0;
				x_position = 150.0;
				x = 2000;
			}
		}
		if (f8 == 1)
		{
			f7 = 1;
			f6 = 0;
			new_x += 60;
			
			if (new_x >= 2200)
			{
				for (int i = 0; i < 10000; i++);
				f7 = 0;
				f1 = 0;
				f2 = 0;
				f3 = 0;
				f4 = 0;
				f5 = 0;
				f6 = 0;
				f8 = 0;
				f9 = 1;
				printf("\ninside f8");
				
			}
		}
		if (f9 == 1)
		{
			f7 = 0;
			f1 = 0;
			f2 = 0;
			f3 = 0;
			f4 = 0;
			f5 = 0;
			f6 = 0;
			f8 = 0;
		}

	}
}
