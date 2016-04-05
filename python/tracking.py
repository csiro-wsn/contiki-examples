# Code from Chapter 10 of Machine Learning: An Algorithmic Perspective
# by Stephen Marsland (http://seat.massey.ac.nz/personal/s.r.marsland/MLBook.html)

# You are free to use, change, or redistribute the code in any way you wish for
# non-commercial purposes, but please maintain the name of the original author.
# This code comes with no warranty of any kind.

# Adapted by Burak Bayramli, 2010


import pylab
import numpy

class Kalman:
    def __init__(self, x_init, cov_init, meas_err, proc_err):
        self.ndim = len(x_init)
        self.A = numpy.array([(1, 0, dt, 0), (0, 1, 0, dt), (0, 0, 1, 0), (0, 0, 0, 1)]);
        self.H = numpy.array([(1, 0, 0, 0), (0, 1, 0, 0)])
        self.x_hat =  x_init
        self.cov = cov_init
        self.Q_k = numpy.eye(ndim)*proc_err
        self.R = numpy.eye(len(self.H))*meas_err

    def update(self, obs):

        # Make prediction
        self.x_hat_est = numpy.dot(self.A,self.x_hat)
        self.cov_est = numpy.dot(self.A,numpy.dot(self.cov,numpy.transpose(self.A))) + self.Q_k

        # Update estimate
        self.error_x = obs - numpy.dot(self.H,self.x_hat_est)
        self.error_cov = numpy.dot(self.H,numpy.dot(self.cov_est,numpy.transpose(self.H))) + self.R
        self.K = numpy.dot(numpy.dot(self.cov_est,numpy.transpose(self.H)),numpy.linalg.inv(self.error_cov))
        self.x_hat = self.x_hat_est + numpy.dot(self.K,self.error_x)
        if ndim>1:
            self.cov = numpy.dot((numpy.eye(self.ndim) - numpy.dot(self.K,self.H)),self.cov_est)
        else:
            self.cov = (1-self.K)*self.cov_est 
            
if __name__ == "__main__":		
    ndim = 4
    ndim_obs = 2
    nsteps = 50
    xcoord = 5.0
    ycoord = 2.0
    vx = 0.5 #m.s
    vy = 1.0 #m/s
    dt = 1.0 #sec
    meas_error = 10.0 #m

    #generate ground truth
    x_true = numpy.array( [(xcoord+i*vx,ycoord+i*vy,vx,vy) for i in range(nsteps)] )
    obs_err = numpy.random.normal(0,numpy.ones(ndim_obs)*meas_error,(nsteps,ndim_obs)) # observations 
    obs = x_true[:,0:2]+obs_err

    #init filter
    proc_error = 0.01;
    init_error = 150.0;
    x_init = numpy.array( [xcoord+init_error, ycoord+init_error, vx, vy] ) #introduced initial xcoord error of 2m 
    cov_init=init_error*numpy.eye(ndim)

    #filtering
    x_hat = numpy.zeros((ndim,nsteps))
    k = Kalman(x_init, cov_init, meas_error, proc_error)    
    for t in range(nsteps):
        k.update(obs[t])
        x_hat[:,t]=k.x_hat

    #plot the results
    pylab.figure()
    pylab.scatter(x_true[:,0],x_true[:,1],s=1, c='g',marker='o', label="true location")
    pylab.scatter(obs[:,0],   obs[:,1],   s=10,c='k',marker='+', label="measured loc")
    pylab.scatter(x_hat[0], x_hat[1], s=10,c='red',marker='s', edgecolors='red', label="estimated loc")
    pylab.xlabel('x [m]')
    pylab.ylabel('y [m]')

    pylab.show()


