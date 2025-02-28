#include "examples.h"

Example::Example(const std::string &_input,
		 const std::vector<Token::Ptr> &_tokens,
		 const AST::Ptr &_ast, const double &_ans)
  : input(_input), tokens(_tokens), ast(_ast), ans(_ans) {}

Token::Ptr append(std::vector<Token::Ptr> &tokens, Token::Ptr token) {
  tokens.push_back(token);
  return token;
}

// SCANNER_INPUT1="3.14"
// PARSER_RESULT1=
//       3.14
Example::Ptr ex0() {
  int line=0, col=0;
  std::string input = "3.14";
  
  std::vector<Token::Ptr> tokens;
  Token::Ptr tk0Pi = append(tokens,Token::number(3.14,line,col)); col += 4;
  Token::Ptr tk1Eof = append(tokens,Token::eof(line,col));        col += 1;

  AST::Ptr ast = AST::number(tk0Pi);
  double ans = 3.14;

  return Example::Ptr(new Example(input,tokens,ast,ans));
}

// SCANNER_INPUT1="(4+5)S*R";
// PARSER_RESULT1=
//       *
//      / \
//     S   R
//     |
//     +
//    / \
//   4   5

Example::Ptr ex1() {
  int line=0, col=0;
  std::string input = "(4+5)S*R";
  
  std::vector<Token::Ptr> tokens;
  Token::Ptr tk0Lparen = append(tokens,Token::lparen(line,col++));
  Token::Ptr tk1Four = append(tokens,Token::number(4,line,col++));
  Token::Ptr tk2Add = append(tokens,Token::add(line,col++));
  Token::Ptr tk3Five = append(tokens,Token::number(5,line,col++));
  Token::Ptr tk4Rparen = append(tokens,Token::rparen(line,col++));
  Token::Ptr tk5Store = append(tokens,Token::keyword("S",line,col++));
  Token::Ptr tk6Times = append(tokens,Token::times(line,col++));
  Token::Ptr tk7Recall = append(tokens,Token::keyword("R",line,col++));
  Token::Ptr tk8Eof = append(tokens,Token::eof(line,col++));

  AST::Ptr ast =
    AST::times(tk6Times,
	       AST::store(tk5Store,
			  AST::add(tk2Add,
				   AST::number(tk1Four),
				   AST::number(tk3Five))),
	       AST::recall(tk7Recall));

  double ans = 81;  

  return Example::Ptr(new Example(input,tokens,ast,ans));
}

Example::Ptr ex2() {
  int line=0, col=0;
  std::string input = "3S+R";
  
  std::vector<Token::Ptr> tokens;
  Token::Ptr tk0Three = append(tokens,Token::number(3,line,col++));
  Token::Ptr tk1Store = append(tokens,Token::keyword("S",line,col++));
  Token::Ptr tk2Add = append(tokens,Token::add(line,col++));
  Token::Ptr tk3Recall = append(tokens,Token::keyword("R",line,col++));
  Token::Ptr tk4Eof = append(tokens,Token::eof(line,col++));

  AST::Ptr ast =
    AST::add(tk2Add,
	     AST::store(tk1Store,
			AST::number(tk0Three)),
	     AST::recall(tk3Recall));

  double ans = 6;

  return Example::Ptr(new Example(input,tokens,ast,ans));
}

Example::Ptr ex3() {
  int line = 0, col = 0;
  std::string input = "(3+2)^2";

  std::vector<Token::Ptr> tokens;
  Token::Ptr tk0lparen = append(tokens, Token::lparen(line, col++));
  Token::Ptr tk1Three = append(tokens, Token::number(3,line,col++));
  Token::Ptr tk2Add = append(tokens,Token::add(line,col++));
  Token::Ptr tk3Two = append(tokens, Token::number(2,line,col++));
  Token::Ptr tk4rparen = append(tokens, Token::rparen(line, col++));
  Token::Ptr tk5Power = append(tokens, Token::power(line,col++));
  Token::Ptr tk6Two = append(tokens, Token::number(2,line,col++));
  Token::Ptr tk7Eof = append(tokens, Token::eof(line, col++));

  AST::Ptr ast = 
  AST::power(tk5Power, 
    AST::add(tk2Add,
      AST::number(tk1Three),
        AST::number(tk6Two)),
          AST::number(tk3Two));

  double ans = 25;

  return Example::Ptr(new Example(input,tokens,ast,ans));
}

//3+2^2 (Juston)
Example::Ptr ex4() {
  int line = 0, col = 0;
  std::string input = "3+2^2";

  std::vector<Token::Ptr> tokens;
  Token::Ptr tk0Three = append(tokens, Token::number(3,line,col++));
  Token::Ptr tk1Add = append(tokens,Token::add(line,col++));
  Token::Ptr tk2Two = append(tokens, Token::number(2,line,col++));
  Token::Ptr tk3Power = append(tokens, Token::power(line,col++));
  Token::Ptr tk4Two = append(tokens, Token::number(2,line,col++));
    Token::Ptr tk5Eof = append(tokens, Token::eof(line, col++));

  AST::Ptr ast = AST::add(tk1Add, 
  AST::number(tk0Three), 
  AST::power(tk3Power,
  AST::number(tk2Two),
  AST::number(tk4Two)));

  double ans = 7;

  return Example::Ptr(new Example(input,tokens,ast,ans));
}

// 4*2*3^2 = 72
Example::Ptr ex5(){
  int line=0, col=0;
  std::string input = "4*2*3^2";

  std::vector<Token::Ptr> tokens;
  Token::Ptr tk0Four = append(tokens,Token::number(4,line,col++));
  Token::Ptr tk1Times = append(tokens,Token::times(line,col++));
  Token::Ptr tk2Two = append(tokens,Token::number(2,line,col++));
  Token::Ptr tk3times = append(tokens,Token::times(line,col++));
  Token::Ptr tk4Three = append(tokens,Token::number(3,line,col++));
  Token::Ptr tk5Power = append(tokens,Token::power(line,col++));
  Token::Ptr tk6Two = append(tokens,Token::number(2,line,col++));
    Token::Ptr tk7Eof = append(tokens, Token::eof(line, col++));

  AST::Ptr ast = AST::times(tk1Times, AST::number(tk0Four),
                    AST::times(tk3times,AST::number(tk2Two),
                        AST::power(tk5Power,AST::number(tk4Three),AST::number(tk6Two))));

  double ans = 72;

  return Example::Ptr(new Example(input, tokens, ast, ans));}

//2^1
Example::Ptr ex6(){
  int line=0, col=0;
  std::string input = "2^1";

  std::vector<Token::Ptr> tokens;
  Token::Ptr tk0Two = append(tokens, Token::number(2,line,col++));
  Token::Ptr tk1Power = append(tokens, Token::power(line,col++));
  Token::Ptr tk2One = append(tokens, Token::number(1,line,col++));
  Token::Ptr tk3Eof = append(tokens,Token::eof(line,col++));

  AST::Ptr ast = AST::power(tk1Power,AST::number(tk0Two),AST::number(tk2One));

  double ans = 2;

  return Example::Ptr(new Example(input, tokens, ast, ans));
}

std::size_t Example::size() { return 6; }
Example::Ptr Example::example(int k) {
  switch(k) {
  case 0: return ex0();
  case 1: return ex1();
  case 2: return ex2();   
  case 3: return ex6();
  case 4: return ex4();
  case 5: return ex5(); 
  default: return NULL;
  }
}
