#include"test.h"
#include"repository.h"
#include<assert.h>

void Test::testRepository()
{
	Repository testRepository;
	Repository testRepository2;
	Repository testRepository3;
	Movie movie("Terminator", "Action", 14000, 1984, "https://www.youtube.com/watch?v=k64P4l2Wmeg");

	assert(testRepository.getSize() == 0);

	testRepository.addMovie(movie);
	testRepository.getAll();
	assert(testRepository.getMovieAtIndex(0) == movie);
	assert(testRepository.getSize() == 1);
	testRepository2 = testRepository;
	assert(testRepository2.getSize() == 1);
	assert(testRepository3.getSize() == 0);
	testRepository3 = testRepository2;
	assert(testRepository3.getSize() == 1);
	Movie movie1("Terminator", "Action", 14000, 1984, "https://www.youtube.com/watch?v=k64P4l2Wmeg");
	assert(testRepository.checkAuthenticity(movie1) == true);
	testRepository3.addMovie(movie1);
	assert(testRepository3.getSize() == 2);
	assert(testRepository.checkAuthenticity(movie) == true);
	testRepository.remove(movie);
	assert(testRepository.getSize() == 0);
	testRepository2.addMovie(movie);
	testRepository.addMovie(movie);
	testRepository.update(movie, movie1);
	assert(testRepository.checkAuthenticity(movie1) == true);
	Movie movie2{ "The Godfather","Drama",25123,1972,"https://www.youtube.com/watch?v=sY1S34973zA" };
	Movie movie3{ "The Dark Knight","Action",18640,2008,"https://www.youtube.com/watch?v=EXeTwQWrcwY" };
	Movie movie4{ "The Godfather Part 2","Drama",15343,1974,"https://www.youtube.com/watch?v=9O1Iy9od7-A" };
	assert(testRepository.checkAuthenticity(movie2) == false);
	testRepository.addMovie(movie2);
	testRepository.addMovie(movie3);
	testRepository.addMovie(movie4);


}

void Test::testMovie()
{

	Movie movie("Terminator", "Action", 14000, 1984, "https://www.youtube.com/watch?v=k64P4l2Wmeg");
	assert(movie.getGenre() == "Action");
	assert(movie.getTitle() == "Terminator");
	assert(movie.getLikes() == 14000);
	assert(movie.getYearOfRelease() == 1984);
	assert(movie.getTrailer() == "https://www.youtube.com/watch?v=k64P4l2Wmeg");
	movie.setGenre("Drama");
	movie.setLikes(12);
	movie.setTitle("Batman");
	movie.setYearOfRelease(10);
	movie.setTrailer("Trailer");
	assert(movie.getGenre() == "Drama");
	assert(movie.getTitle() == "Batman");
	assert(movie.getLikes() == 12);
	assert(movie.getYearOfRelease() == 10);
	assert(movie.getTrailer() == "Trailer");

}