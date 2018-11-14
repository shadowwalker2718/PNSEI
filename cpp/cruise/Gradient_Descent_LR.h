// https://helloacm.com/cc-linear-regression-tutorial-using-gradient-descent/

double x[] = {1, 2, 4, 3, 5};
double y[] = {1, 3, 3, 2, 5};

double b0 = 0;
double b1 = 0;
double alpha = 0.01;

for (int i = 0; i < 20; i ++) {
    int idx = i % 5;
    double p = b0 + b1 * x[idx];
    double err = p - y[idx];
    b0 = b0 - alpha * err;
    b1 = b1 - alpha * err * x[idx];
}

// http://eric-yuan.me/linear-regression/

/*
If the training example is very large, we can use this method, and update θj after every single iteration. Maybe we can get θj  which good enough by part of the example, we can avoid continue training instead of using whole example to do training.
*/
