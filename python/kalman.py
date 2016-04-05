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
        self.A = numpy.eye(ndim)        #state transition model
        self.H = numpy.eye(ndim)        #observation model
        self.x_hat =  x_init
        self.cov = cov_init
        self.Q_k = numpy.eye(ndim)*proc_err #covariance matrix of process noise
        self.R = numpy.eye(len(self.H))*meas_err   #covariance matrix of observation noise
        
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
    print "***** 1d ***********"
    ndim = 1
    nsteps = 50
    k = Kalman(numpy.array([0]), numpy.eye(ndim),0.01, 1e-5) #this assumes initial value not known
    x_init=numpy.array([-0.37727])
    cov_init=1.0*numpy.ones((ndim))
    obs = numpy.random.normal(x_init,cov_init,(ndim, nsteps))
    xhat = numpy.zeros(nsteps)
    for t in range(nsteps):
        k.update(obs[:,t])
        xhat[t]=k.x_hat        
    print "Constant value estimate after 50 iterations: %f" % xhat[-1]

    pylab.figure()
    pylab.plot(obs[0],'k+',label='noisy measurements')
    pylab.plot(xhat,'b-',label='a posteri estimate')
    pylab.axhline(x_init[0],color='g',label='truth value')
    #legend()
    pylab.xlabel('Iteration')
    pylab.ylabel('Voltage')
    pylab.show()

#    print "***** 2d ***********"
#    ndim = 2
#    nsteps = 50
#    k = Kalman(ndim)    
#    x_init=numpy.array([-0.37727, 2.333])
#    cov_init=0.1*numpy.ones((ndim))
#    obs = numpy.zeros((ndim, nsteps))
#    for t in range(nsteps):
#        obs[:, t] = numpy.random.normal(x_init,cov_init)
#    for t in range(ndim,nsteps):
#        k.update(obs[:,t])
#    print k.x_hat_est
#    

