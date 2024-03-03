#include"test.h"
#include"DynamicVector.h"
#include<assert.h>

void Test::testDynamicVector()
{
	DynamicVector<Movie> vector{ 5 };

	Movie movie("Terminator", "Action", 14000, 1984, "https://www.youtube.com/watch?v=k64P4l2Wmeg");

	assert(vector.getSize() == 0);

	vector.add(movie);

	assert(vector.getSize() == 1);

	DynamicVector<Movie> vector2 = vector;
	assert(vector2.getSize() == 1);

	DynamicVector<Movie> vector3{};
	assert(vector3.getSize() == 0);
	vector3 = vector2;
	assert(vector3.getSize() == 1);
	Movie movie1("Terminator", "Action", 14000, 1984, "https://www.youtube.com/watch?v=k64P4l2Wmeg");
	vector3.add(movie1);
	assert(vector3.getSize() == 2);
	assert(vector.checkAuthenticity(movie) == true);
	vector.remove(movie);
	assert(vector.getSize() == 0);
	vector.add(movie);
	vector.update(movie, movie1);
	assert(vector.checkAuthenticity(movie1) == true);
	Movie movie2{ "The Godfather","Drama",25123,1972,"https://www.youtube.com/watch?v=sY1S34973zA" };
	Movie movie3{ "The Dark Knight","Action",18640,2008,"https://www.youtube.com/watch?v=EXeTwQWrcwY" };
	Movie movie4{ "The Godfather Part 2","Drama",15343,1974,"https://www.youtube.com/watch?v=9O1Iy9od7-A" };
	vector.add(movie2);
	vector.add(movie3);
	vector.add(movie4);


}