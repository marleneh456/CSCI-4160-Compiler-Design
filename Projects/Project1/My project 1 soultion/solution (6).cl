(*
PROGRAMMER: Marlene Habib
PROGRAM#:1
DUE DATE: Monday, 02/05/2023
INSTRUCTOR: Dr. Dong
DESCRIPTION OF PROGRAM: This program utilizes a list as a stack in order to perform a command on e for evalute, d for display, use x for stop and use * to multiplied the stack.
*)

(*
   The class A2I provides integer-to-string and string-to-integer
conversion routines.  To use these routines, either inherit them
in the class where needed, have a dummy variable bound to
something of type A2I, or simpl write (new A2I).method(argument).
*)


(*
   c2i   Converts a 1-character string to an integer.  Aborts
         if the string is not "0" through "9"
*)
class A2I {

     c2i(char : String) : Int {
	if char = "0" then 0 else
	if char = "1" then 1 else
	if char = "2" then 2 else
        if char = "3" then 3 else
        if char = "4" then 4 else
        if char = "5" then 5 else
        if char = "6" then 6 else
        if char = "7" then 7 else
        if char = "8" then 8 else
        if char = "9" then 9 else
        { abort(); 0; }  -- the 0 is needed to satisfy the typchecker
        fi fi fi fi fi fi fi fi fi fi
     };

(*
   i2c is the inverse of c2i.
*)
     i2c(i : Int) : String {
	if i = 0 then "0" else
	if i = 1 then "1" else
	if i = 2 then "2" else
	if i = 3 then "3" else
	if i = 4 then "4" else
	if i = 5 then "5" else
	if i = 6 then "6" else
	if i = 7 then "7" else
	if i = 8 then "8" else
	if i = 9 then "9" else
	{ abort(); ""; }  -- the "" is needed to satisfy the typchecker
        fi fi fi fi fi fi fi fi fi fi
     };

(*
   a2i converts an ASCII string into an integer.  The empty string 
is converted to 0.  Signed and unsigned strings are handled.  The
method aborts if the string does not represent an integer.  Very
long strings of digits produce strange answers because of arithmetic 
overflow.
(*2019Spring*)
*)
     a2i(s : String) : Int {
        if s.length() = 0 then 0 else
	if s.substr(0,1) = "-" then ~a2i_aux(s.substr(1,s.length()-1)) else
        if s.substr(0,1) = "+" then a2i_aux(s.substr(1,s.length()-1)) else
           a2i_aux(s)
        fi fi fi
     };

(*
  a2i_aux converts the usigned portion of the string.  As a programming
example, this method is written iteratively.
*)
     a2i_aux(s : String) : Int {
	(let int : Int <- 0 in	
           {	
               (let j : Int <- s.length() in
	          (let i : Int <- 0 in
		    while i < j loop
			{
			    int <- int * 10 + c2i(s.substr(i,1));
			    i <- i + 1;
			}
		    pool
		  )
	       );
              int;
	    }
        )
     };

(*
    i2a converts an integer to a string.  Positive and negative 
numbers are handled correctly.  
*)
    i2a(i : Int) : String {
	if i = 0 then "0" else 
        if 0 < i then i2a_aux(i) else
          "-".concat(i2a_aux(i * ~1)) 
        fi fi
    };
	
(*
    i2a_aux is an example using recursion.
*)		
    i2a_aux(i : Int) : String {
        if i = 0 then "" else 
	    (let next : Int <- i / 10 in
		i2a_aux(next).concat(i2c(i - next * 10))
	    )
        fi
    };

};





(* add your solution below *)

class List {
   -- Define operations on empty lists.

   isNil() : Bool { true };

   -- Since abort() has return type Object and head() has return type
   -- Int, we need to have an Int as the result of the method body,
   -- even though abort() never returns.

   head()  : String { { abort(); ""; } };

   -- As for head(), the self is just to make sure the return type of
   -- tail() is correct.

   tail()  : List { { abort(); self; } };

   -- When we cons and element onto the empty list we get a non-empty
   -- list. The (new Cons) expression creates a new list cell of class
   -- Cons, which is initialized by a dispatch to init().
   -- The result of init() is an element of class Cons, but it
   -- conforms to the return type List, because Cons is a subclass of
   -- List.

   cons(i : String) : List {
      (new Cons).init(i, self)
   };

};


--Cons class inherits from List class
class Cons inherits List {

   --hold the value of node in the list
   first : String;	

   --next node in the list
   remainder : List;	

   --isNil method overides the corresponding method in the List class and return false
   isNil() : Bool { false };

   --the head method returns the first element of the list	
   head()  : String { first };

   --the tail method returns the remainder of the list
   tail()  : List { remainder };

   --init method initializes a new Cons node with i and the remainder of rest of the list
   init(i : String, rest : List) : List {
      {
	   first <- i;
	   remainder <- rest;
	   self;
      }
   };

};


class Main inherits IO {

  --This method print the display
  print(list_item : List) : Object {
      if list_item.isNil() then out_string("")
         else {
              out_string(list_item.head());
	          out_string("\n");
			  print(list_item.tail());
		      }
      fi
   };

 --This method does the evaluate the stack
 command_e(list_item : List) : List {
{
	  -- Check if the head of the list is "*"
      if (list_item.head() = "*") then 
        let convert: A2I <- new A2I, -- Initializes A2I object
            numberone: Int <- convert.a2i(list_item.tail().head()), -- Takes numberOne
            numbertwo: Int <- convert.a2i(list_item.tail().tail().head()), -- Takes numberTwo
            times: Int <- (numberone * numbertwo) --Times two numbers
        in 
          list_item <- list_item.tail().tail().tail().cons(convert.i2a(times))
      else 
        list_item
      fi;
    }
};

  


  main():Object { {
    out_string(">"); --Print >
	
	--Initialize the list_item as a new List.
    let char: String <- in_string(),  
        list_item: List <- new List        
    in
      while (not char = "x") loop --While loop for the commands
        {
          if (char = "*") then
            list_item <- list_item.cons("*") --add to the stack if there is *
          else
            if (char = "d") then  --For display
                print(list_item)
            else
              if (char = "e") then  --For evaluate the stack
                list_item <- command_e(list_item)
              else
                list_item <- list_item.cons(char)    -- For any other character, add it to the stack.
              fi
            fi
          fi;
          out_string(">"); --Print >
          char <- in_string(); --Read the next character
        }
      pool; --End of loop
    out_string("COOL program successfully executed\n"); --Print the exit
   }
  };

};