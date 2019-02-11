#include "stdafx.h"
#include "FileWriter.h"
#include <iostream>
#include <fstream>


void CSVFileWriter::write(std::string filename, std::vector<Film> films)
{
	filename.append(".csv");
	std::ofstream csvFile{ filename };
	for (Film & item : films)
		csvFile << item.getTitle() << "," << item.getYear() << "," << item.getGenre() << "," << item.getLikes() << '\n';
}


void HTMLFileWriter::write(std::string filename, std::vector<Film> films)
{
	filename.append(".html");
	std::ofstream htmlFile{ filename };
	htmlFile << "<!DOCTYPE html>\n" << "<html>\n" << "<head>\n" << "<title>Watchliste</title>\n" << "</head>\n" << "<body>\n" << "<table border = \"1\">\n";
	htmlFile << "<tr>  <td>Title</td>  <td>Year</td>  <td>Genre</td>  <td>Likes</td>  <td>Trailer</td>  </tr> \n";
	
	for (Film & item : films) {
		htmlFile << "<tr>\n<td>" << item.getTitle() << "</td>\n<td>" << item.getYear() << "</td>\n<td>" << item.getGenre() << "</td>\n<td>" << item.getLikes();
		htmlFile << "</td>\n<td><a href =\"" << item.getLink() << "\">" << item.getTitle() << "</a></td>\n</tr>" << '\n';
	}

	htmlFile << "</table>\n</body></html>";
}
