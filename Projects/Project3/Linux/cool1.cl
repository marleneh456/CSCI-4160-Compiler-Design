(* Test the basic functionality of the COOL syntax analyzer. *)
class Main inherits IO {
	x : Int <- 0
	y : String <- "something";

	f(a:Int, b:Int) : Int {
		a+b
	};

    main() : SELF_TYPE {
		{
		m  <- new Main; 
		x.f(x,y);
		m@Main.f(1, 3);
		g(x y);
		g(x,y, );
		1;
		x < y < z;
		x = y = z;
		x <- y <- z;
		}
	};
};


