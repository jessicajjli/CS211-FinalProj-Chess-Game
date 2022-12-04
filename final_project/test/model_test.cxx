#include "model.hxx"
#include <catch.hxx>

///
/// Member function definitions for Test_access
///

struct Test_access
{
    Model& model;

    // Constructs a `Test_access` with a reference to the Model under test.
    explicit Test_access(Model&);
    // Sets the player at `posn` to `player`.
    void set_player(Position posn, Piece piece);
    // Gives direct access to `model.next_moves_` so our tests can modify it:
    //Move_map& next_moves();


};

Test_access::Test_access(Model& model)
        : model(model)
{ }
void
Test_access::set_player(Position posn, Piece piece)
{
    Piece p = Piece(piece);
    model.squares()[posn.x][posn.y] = p;
}
//
// Preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//


TEST_CASE("light winner") //MODEL TEST 1
//SPEC 10
//Checks that game is over when king captured
//Checks that captured king vanishes from board
//Checks that a winner can be declared
{
    Model model;
    Test_access access(model);

    //check initial winner
    CHECK(model.get_winner() == -1);
    //check initial turn is light
    CHECK(model.get_turn() == 1);
    //set king on board to be captured
    access.set_player({4,0},
                      Piece(Piece_type::king,
                            {4,0},
                            0,{}, true));
    access.set_player({3,1},
                      Piece(Piece_type::pawn,
                            {3,1},1,
                            {}, true));
    //light piece captures king
    model.play_move({4,0}, {3, 1}, model.squares()[3][1]); //light
    //check turn switches to dark
    CHECK(model.get_turn() == 0);

    //check winner is light
    CHECK(model.get_winner()== 1);
}

// Test 2: check that a piece moving from a position actually dissapears from
// that original position
TEST_CASE("piece disapears from original position")
//SPEC 4
{
    Model model;
    Test_access access(model);
    //check initial winner
    CHECK(model.get_winner() == -1);
    //check initial turn is light
    CHECK(model.get_turn() == 1);
    //set rook on board to be captured
    access.set_player({5,0},
                      Piece(Piece_type::rook,
                            {5,0},
                            0,{}, true));
    access.set_player({4,1}, Piece(
            Piece_type::pawn,{4,1}, 1,
            {}, true));
    //light piece captures rook
    model.play_move({5,0}, {4, 1}, model.squares()[4][1]); //light
    //check turn switches to dark
    CHECK(model.squares()[4][1] == Piece(Piece_type::none,
                                         {4,1}, -1,
                                         {},false));

}


// Test 3: check that a piece moving into a position is actually there
//SPEC
TEST_CASE("piece moves into position is actually there")
//Checks that game is over when king captured
//Checks that captured king vanishes from board
//Checks that a winner can be declared
{
    Model model;
    Test_access access(model);
    //check initial winner
    CHECK(model.get_winner() == -1);
    //check initial turn is light
    CHECK(model.get_turn() == 1);
    //set rook on board to be captured
    access.set_player({5,0},
                      Piece(Piece_type::king,
                            {5,0},
                            1,{}, true));
    access.set_player({4,0},
                      Piece(Piece_type::pawn,
                            {4,0},
                            0,{}, true));

    //light piece captures rook
    model.play_move({4,0},{5, 0}, model.squares()[5][0]); //light
    //check turn switches to dark
    model.squares()[4][0].set_valid_moves(model.squares());
    CHECK(model.squares()[4][0].get_active() == true);
    CHECK(model.get_winner() == 1);
}


// Test 4: Test that our turn can be changed

TEST_CASE("turn changes") //MODEL TEST 4
//SPEC 4
//Checks play move works, player can move and disppear from old square
//checks turn changes
//check that dark can win
{
    Model model;
    Test_access access(model);

    //check initial winner
    CHECK(model.get_winner() == -1);
    //check initial turn is light
    CHECK(model.get_turn() == 1);


    //light king set
    access.set_player({0,3},
                      Piece(Piece_type::king,
                            {0,3},1,
                            {}, true));

    //set pawn on board
    access.set_player({1,1},
                      Piece(Piece_type::pawn,
                            {1,1},
                            0,{}, true));


    //light king moves
    model.play_move({0,3}, {0, 2}, model.squares()[0][2]); //light
    CHECK(model.get_turn() == 0); //changes to dark turn
    model.play_move({1,1}, {0, 2}, model.squares()[0][2]); //dark


    //check winner
    CHECK(model.get_winner()== -1);
}
// Test 5: Checks illegal/possible moves
TEST_CASE("check illegal and possible moves") //MODEL TEST 5
// OR illegal move check if full game is too hard
{
    Model model;
    Test_access access(model);
    //check initial winner
    CHECK(model.get_winner() == -1);
    //check initial turn is light
    CHECK(model.get_turn() == 1);
    //set player on board
    access.set_player({6,7},
                      Piece(Piece_type::knight,
                            {6,7},
                            1,{}, true));
    //show possible moves
    model.squares()[6][7].set_valid_moves(model.squares());
    Position_set valid_moves = model.squares()[6][7].get_valid_moves();
    Position_set predicted_invalid_moves = {{4,8},{5,9},{7,9},
                                            {8,6},{8,8}};
    //check illegal move
    CHECK(valid_moves != predicted_invalid_moves);


}