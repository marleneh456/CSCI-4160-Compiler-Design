(* Test the basic functionality of the Tiger lexical analyzer. *)
class Main inherits IO {
    main() : SELF_TYPE {
	(let c : Complex <- (new Complex).init(1, 1) in
	    {
	     -- trivially equal (see CoolAid)
	        if c.reflect_X() = c.reflect_0()
	        then out_string("=)")
	        else out_string("=(")
	        fi
		-- equal
	        (*if c.reflect_X().reflect_Y().equal(c.reflect_0())
	        then out_string("=)")
	        (* else out_string("=(") *)
	        fi;
			*)
	    }
	)
    };
};

(* Finally, we have
	(* an unclosed nested comment!
	*)
	something
