/*TODO
	generic property sheet with all 3rd party deps included and linked etc.
	use each 3rd party lib in at least a hello world style to confirm that they are there and working

*/

#include "lua.hpp"
#include "glm.hpp"
#include "spdlog.h"
//#include "SFML\System.hpp"

void main()
{
	glm::vec3 a,b;

	//sf::Vector2f c, d;

	a = a + b;

	auto console = spdlog::stdout_logger_mt("console");
	console->info("Welcome to spdlog!");
}