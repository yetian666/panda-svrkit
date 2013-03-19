#pragma once

class Nocopyable
{
protected:
	Nocopyable();
	~Nocopyable();
private:
	Nocopyable( const Nocopyable& nocopy );
	const Nocopyable& operator=(const Nocopyable& nocopy);
};

