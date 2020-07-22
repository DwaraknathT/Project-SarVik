#pragma once
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Sphere.h"
#include "Cube.h"
#include "GuideLines.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include<thread>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct data
{
	double x;
	double y;
	double z;
	double dosage;
};
struct data mydata[1331];
void CreateCylinFromTo(int index1, int index2, std::vector<Cylinder> & cylin, glm::vec4 colour, Shader shader)
{
	for (int i = index1; i < index2; i++)
	{
		float x = mydata[i].x;
		float y = mydata[i].y;
		float z = mydata[i].z;
		float r = sqrt(pow((x - 0.1), 2) + pow(y, 2));

		//printf("%f, %f, %f,\n", x, y, r);
		cylin[i] = Cylinder(r, 1.0f, glm::vec3(x, y, z), colour); //radius, hieght 
		cylin[i].SetShader(shader);
		cylin[i].RotateX(90.0f);
	}
}
class Simulation
{
private:
	Shader m_Shader;
	Sphere sphere;
	Sphere sphere2;
	GuideLines guide;
	
	Cylinder ref_cyl; //reference line 
	//Cylinder cylin3d[1331][4]; //each point has 4 cylinders 

	Cuboid cuboid;
	Cube cube;
	glm::vec4 red = glm::vec4(0.0f, 0.1f, 0.0f, 1.0f);
	glm::vec4 cube_color = glm::vec4(0.0f, 1.0f, 0.0f, 0.20f);
	glm::vec4 ref_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	int numSteps = 1331 / 4;

	//Parser p;
public:
	std::vector<Cylinder> cylin;
	Simulation()
	{
	}
	Simulation(Shader p_Shader)
	{

		sphere = Sphere(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0, 1.0f, 0.0f, 0.075f));
		sphere2 = Sphere(glm::vec3(1.0f, 0.4f, -0.2f), glm::vec4(1.0f, 0.0f, 0.0f, 0.075f));
		guide = GuideLines(glm::vec3(0.0f, 0.0f, 0.0f));
		m_Shader = p_Shader;
		sphere.SetShader(m_Shader);
		sphere2.SetShader(m_Shader);
		guide.SetShader(m_Shader);
		cube = Cube(glm::vec3(0.0f, 0.5f, 0.57f), 2.0f, cube_color);
		cube.SetShader(m_Shader);
		cuboid = Cuboid(glm::vec3(1.0f, 2.0f, 0.0f), 1.0f, 1.0f, 1.0f, red);
		ref_cyl = Cylinder(0.01f, 1.0f, glm::vec3(0.1f, 0.0, 0.0), ref_color);
		ref_cyl.SetShader(m_Shader);
		cylin.resize(1331);
		//load data 
		FILE *fp = fopen("datasets2D.csv", "r");
		if (fp != NULL)
		{
			char a[30];
			char b[30];
			char c[30];
			char d[30];
			int i = 0;
			while (i < 1331)
			{
				fscanf(fp, "%s, %s, %s, %s \n", a);

				mydata[i].x = 1.0f*(double)atof(a);

				i++;
			}
			i = 0;
			while (i < 1331)
			{
				fscanf(fp, "%s, %s, %s, %s \n", b);

				mydata[i].y = 1.0f*(double)atof(b);

				i++;
			}
			i = 0;
			while (i < 1331)
			{
				fscanf(fp, "%s, %s, %s, %s \n", c);

				mydata[i].z = 1.0f*(double)atof(c);

				i++;
			}
			i = 0;
			while (i < 1331)
			{
				fscanf(fp, "%s, %s, %s, %s \n", d);

				mydata[i].dosage = 1.0f*(double)atof(d);

				i++;
			}

		}
		else
		{
			printf("unable to open");
		}


		fclose(fp);
		int step = 1331 / 4;
		std::thread th1(CreateCylinFromTo,0,step*1,cylin,red,m_Shader);

		std::thread th2(CreateCylinFromTo, step*1 , step * 2, cylin, red, m_Shader);

		std::thread th3(CreateCylinFromTo, step*2 , step * 3, cylin, red, m_Shader);

		std::thread th4(CreateCylinFromTo, step*3 , 1331, cylin, red, m_Shader);

		th1.join();
		th2.join();
		th3.join();
		th4.join();

		/*for (int i = 0; i < 1331; ++i)
		{
			float x = mydata[i].x;
			float y = mydata[i].y;
			float z = mydata[i].z;
			float r = sqrt(pow((x), 2) + pow(y, 2));

			printf("%f, %f, %f,\n", x, y, r);
			cylin[i] = Cylinder(r, 1.0f, glm::vec3(x, y, z), red); //radius, hieght
			cylin[i].SetShader(m_Shader);
			cylin[i].RotateX(90.0f);
		}
		for (int i = 0; i < 1331; ++i)
		{
			float x = mydata[i].x;
			float y = mydata[i].y;
			float z = mydata[i].z;
			float r = sqrt(pow((x - 0.05), 2) + pow(y, 2));

			printf("%f, %f, %f,\n", x, y, r);
			cylin[i] = Cylinder(r, 1.0f, glm::vec3(x, y, z), red); //radius, hieght
			cylin[i].SetShader(m_Shader);
			cylin[i].RotateX(90.0f);
		}
		for (int i = 0; i < 1331; ++i)
		{
			float x = mydata[i].x;
			float y = mydata[i].y;
			float z = mydata[i].z;
			float r = sqrt(pow((x - 0.1), 2) + pow(y, 2));

			printf("%f, %f, %f,\n", x, y, r);
			cylin[i] = Cylinder(r, 1.0f, glm::vec3(x, y, z), red); //radius, hieght
			cylin[i].SetShader(m_Shader);
			cylin[i].RotateX(90.0f);
		}
		for (int i = 0; i < 1331; ++i)
		{
			float x = mydata[i].x;
			float y = mydata[i].y;
			float z = mydata[i].z;
			float r = sqrt(pow((x - 0.15), 2) + pow(y, 2));

			printf("%f, %f, %f,\n", x, y, r);
			cylin[i] = Cylinder(r, 1.0f, glm::vec3(x, y, z), red); //radius, hieght
			cylin[i].SetShader(m_Shader);
			cylin[i].RotateX(90.0f);
		}*/



		cuboid.SetShader(m_Shader);
	}

	
	
	void Begin()
	{

	}
	void Update()
	{


	}
	void Draw()
	{
		cube.Draw();
		ref_cyl.Draw();
		guide.Draw();
		for (int i = 0; i < 4; ++i)
		{
			cylin[i].Draw();
		}




		//cuboid.Draw();
	}
};