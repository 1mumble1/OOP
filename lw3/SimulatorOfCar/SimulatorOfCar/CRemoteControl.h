#pragma once

class Car;

class RemoteControl
{
public:
	RemoteControl(Car& car, std::istream& input, std::ostream& output)
		: m_car{ car }
		, m_input{ input }
		, m_output{ output }
	{
	}

	void ExecuteCommand() const;

private:
	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;
};