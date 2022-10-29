function [root]=Bisection_Method(func_expression, x_lower, x_upper, es)
    x = x_upper;
    fu = evstr(func_expression); //evaluate the function at x_upper
    x = x_lower;
    fl = evstr(func_expression); //evaluate the function at x_lower
    //***********************************************************
    //test to see if there is a root in the interval
    if (fu*fl >= 0) then
        root = 'no root in interval given';
    else
        //there is a root in the interval
        exact_solution = 'notfound';
        ea = 100;
        xr_new =(x_upper + x_lower)/2;
        //*******************************************************
        //iteratively progress toward to root until it is found or it
        //is approximated with a relative error less than required
        while ea > es & exact_solution == 'notfound',
            x = xr_new;
            fr = evstr(func_expression);
            x = x_lower;
            fl = evstr(func_expression);
            //***************************************************
            if(fl*fr < 0) then
                x_upper = xr_new;
            elseif(fl*fr > 0) then
                x_lower = xr_new;
            elseif(fl*fr == 0) then
                root = xr_new;
                exact_solution = 'found';
            end //of if statement
            //***************************************************
            //calculate the approximate relative error for the iteration
            xr_old = xr_new;
            xr_new =(x_upper + x_lower)/2;
            ea = abs((xr_new - xr_old)/xr_new)*100;
        end //of while loop 
        //*******************************************************
        //if error criterion has been met but the exact answer has not
        //been found, set the root to the adequate approximation.
        if (exact_solution == 'notfound') then
            root = xr_new;
        end //of if statement
        //*******************************************************      
    end //of if-else statement
    //***********************************************************
endfunction
