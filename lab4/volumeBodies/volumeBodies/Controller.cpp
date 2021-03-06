#include "stdafx.h"
#include "controller.h"
#include "Body.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"
#include "Parallelepiped.h"

using namespace std;
using namespace std::placeholders;

bool CBodyController::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	return false;
}

void CBodyController::Info()
{
	m_output << "available commands:\n"
		<< "Sphere <radius> <density>\n"
		<< "Parallelepiped <density> <width> <height> <depth>\n"
		<< "Cone <height> <radius> <density>\n"
		<< "Cylinder <height> <radius> <density>\n";
}

void CBodyController::PrintBodies(vector<shared_ptr<CBody>> const &bodies, ostream &output)
{
	if (bodies.empty())
	{
		output << "Not found of bodies\n";
	}
	else
	{
		for (auto &body : bodies)
		{
			output << body->ToString();
		}
	}
}

void CBodyController::FindBodyWithMaxMass(std::vector<std::shared_ptr<CBody>> const & bodies, std::ostream & output)
{
	if (!bodies.empty())
	{
		auto maxMass = [](shared_ptr<CBody> const &x, shared_ptr<CBody> const &y)
		{
			return x->GetMass() < y->GetMass();
		};
		output << "Body with max mass is "<< (*max_element(bodies.begin(), bodies.end(), maxMass))->ToString();
	}
}

void CBodyController::FindBodyWithMinWeightInWater(std::vector<std::shared_ptr<CBody>> const & bodies, std::ostream & output)
{
	static const double DENSITY_WATER = 1000.0;
	static const double G = 9.8;
	if (!bodies.empty())
	{
		auto minWeight = [](shared_ptr<CBody> const &x, shared_ptr<CBody> const &y)
		{
			return ((x->GetDensity() - DENSITY_WATER) * G * x->GetVolume()) < ((y->GetDensity() - DENSITY_WATER)* G * y->GetVolume());
		};
		output << "Body with min weight in water is " << (*min_element(bodies.begin(), bodies.end(), minWeight))->ToString();
	}
}

bool CBodyController::CreateCylinder(std::istream & args)
{
	double height;
	double radius;
	double density;
	if (!(args >> height) || !(args >> radius) || !(args >> density))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Cylinder <height> <radius> <density>\n";
		return false;
	}
	try
	{
		shared_ptr<CBody> cylinder = make_shared<CCylinder>(height, radius, density);
		m_bodies.push_back(cylinder);
	}
	catch (invalid_argument const &e)
	{
		m_output << e.what();
		return false;
	}
	return true;
}

bool CBodyController::CreateCone(std::istream & args)
{
	double height;
	double radius;
	double density;
	if (!(args >> height) || !(args >> radius) || !(args >> density))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Cone <height> <radius> <density>\n";
		return false;
	}
	try
	{
		shared_ptr<CBody> cone = make_shared<CCone>(height, radius, density);
		m_bodies.push_back(cone);
	}
	catch(invalid_argument const &e)
	{
		m_output << e.what();
		return false;
	}
	return true;
}

bool CBodyController::CreateSphere(std::istream & args)
{
	double radius;
	double density;
	if (!(args >> radius) || !(args >> density))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Sphere <radius> <density>\n";
		return false;
	}

	try
	{
		shared_ptr<CBody> sphere = make_shared<CSphere>(radius, density);
		m_bodies.push_back(sphere);
	}
	catch (invalid_argument const &e)
	{
		m_output << e.what();
		return false;
	}
	return true;
}

bool CBodyController::CreateParallelepiped(std::istream & args)
{
	double width;
	double density;
	double height;
	double depth;
	if (!(args >> density) || !(args >> width) || !(args >> height) || !(args >> depth))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Parallelepiped <density> <width> <height> <depth>\n";
		return false;
	}
	try
	{
		shared_ptr<CBody> parallelepiped = make_shared<CParallelepiped>(density, width, height, depth);
		m_bodies.push_back(parallelepiped);
	}
	catch (invalid_argument const &e)
	{
		m_output << e.what();
		return false;
	}
	return true;
}

CBodyController::CBodyController(vector<shared_ptr<CBody>> & bodies, istream & input, ostream & output)
	: m_bodies(bodies)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ {"Cylinder", bind(&CBodyController::CreateCylinder, this, _1) },
		{ "Cone", bind(&CBodyController::CreateCone, this, _1) },
		{ "Sphere", bind(&CBodyController::CreateSphere, this, _1) },
		{ "Parallelepiped", bind(&CBodyController::CreateParallelepiped, this, _1) }
})
{
}


