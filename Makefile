default:
	# @make test_walking_random_map
	@make test_walking_manual

# Compile Tests
compile_entities:
	@clang++ -c class-entity/Entity.cpp class-entity/Enemy.cpp class-entity/Player.cpp class-entity/Box.cpp # This happens to compile all entity classes
	@mv Entity.o ./class-compiled
	@mv Player.o ./class-compiled
	@mv Enemy.o ./class-compiled
	@mv Box.o ./class-compiled

compile_game:
	@clang++ -c class-entity/Entity.cpp class-entity/Player.cpp class-entity/Enemy.cpp class-entity/Box.cpp class-game-entity/GameManager.cpp # This happens to compile these files into classes.
	@mv Entity.o ./class-compiled
	@mv Player.o ./class-compiled
	@mv Enemy.o ./class-compiled
	@mv Box.o ./class-compiled
	@mv GameManager.o ./class-compiled

# install svn
svn:
	@sudo apt-get install subversion < test-scripts/svn.txt
	@svn stat


# Test Makes
OBJ = class-compiled/Entity.o class-compiled/Player.o class-compiled/Enemy.o class-compiled/Box.o class-compiled/GameManager.o

test_walking_manual: compile_game
	@clang++ $(OBJ) maps/map_10x10.cpp test-mains/maintest_walking.cpp -o walk
	@./walk
	@rm walk

test_walking_random_map: compile_game
	@clang++ $(OBJ) maps/map_random.cpp test-mains/maintest_walking.cpp -o walk
	@./walk
	@rm walk

test_walking_5x5: compile_game
	@clang++ $(OBJ) maps/map_5x5.cpp test-mains/maintest_walking.cpp -o walk
	@./walk < test-scripts/walking.txt
	@rm walk

test_walking_10x10: compile_game
	@clang++ $(OBJ) maps/map_10x10.cpp test-mains/maintest_walking.cpp -o walk
	@./walk < test-scripts/walking.txt
	@rm walk

test_walking_hallway_x: compile_game
	@clang++ $(OBJ) maps/map_horizontal_hallway.cpp test-mains/maintest_walking.cpp -o walk
	@./walk
	@rm walk

test_walking_hallway_y: compile_game
	@clang++ $(OBJ) maps/map_vertical_hallway.cpp test-mains/maintest_walking.cpp -o walk
	@./walk
	@rm walk

test_experience: compile_game
	@clang++ $(OBJ) maps/map_10x10.cpp test-mains/maintest_experience.cpp -o walk
	@./walk # < test-scripts/walking.txt
	@rm walk

test_hurting: compile_game
	@clang++ $(OBJ) maps/map_10x10.cpp test-mains/maintest_hurting.cpp -o walk
	@./walk < test-scripts/walking.txt
	@rm walk

test_enemy: compile_game
	@clang++ $(OBJ) maps/map_5x5.cpp test-mains/maintest_enemy.cpp -o walk
	@./walk # < test-scripts/quickstart.txt
	@rm walk

test_arena: compile_game
	@clang++ $(OBJ) maps/map_10x10.cpp test-mains/maintest_arena.cpp -o walk
	@./walk # < test-scripts/quickstart.txt
	@rm walk

test_boxes: compile_game
	@clang++ $(OBJ) maps/map_10x10.cpp test-mains/maintest_boxes.cpp -o walk
	./walk # < test-scripts/quickstart.txt
	@rm walk

# Final Product
game: compile_game
	@clang++ $(OBJ) maps/map_random.cpp game-mains/main_normal.cpp -o game-compiled/main_normal
	@ chmod 700 game-compiled/main_normal # My friend wasn't able to test this file on their CS50 IDE unless they did this, so I'll do this before sending it.
	@./game-compiled/main_normal

run:
	@./game-compiled/main_normal