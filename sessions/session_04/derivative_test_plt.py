#!/usr/bin/env python
# coding: utf-8

# ## Example of plotting and fitting in python
# 
# Programmer:  Ralf Bundschuh    bundschuh.2@osu.edu
# 
# Versions:
# 
#   2021-12-29  initial version

# Load matplotlib und numpy so that we can use them

# In[1]:


from matplotlib import pyplot as plt
import numpy as np


# Make sure the matplotlib graphs show up in our notebook

# In[2]:


# get_ipython().run_line_magic('matplotlib', 'inline')


# Load data from our derivative calculation

# In[3]:


derivative_data=np.loadtxt('derivative_test.dat')


# Look at first five lines of data to make sure it was read correctly

# In[4]:


derivative_data[:5]


# Extract only the rows with a log10(mesh size) (first column) between -1 and -8 since those are what we want to fit to

# In[5]:


linear_range_data=derivative_data[(derivative_data[:,0]>=-8.) & (derivative_data[:,0]<=-1.)]
linear_range_data


# Fit a straight line (polynomial of degree 1) to the first two columns (note that column indices in python are zero-based!)
# 
# The first entry in the result is the slope and the second entry is the offset

# In[6]:


linear_fit_coefficients=np.polyfit(linear_range_data[:,0],linear_range_data[:,1],deg=1)
linear_fit_coefficients


# Make a nice looking string out of the fit coefficients

# In[7]:


fit_title='{:.1f}*x{:+.1f}'.format(linear_fit_coefficients[0],linear_fit_coefficients[1])
fit_title


# Generate the actual plot

# In[8]:


# set up the plot
fig=plt.figure()
ax1=fig.add_subplot(111)

# axes labels and title
ax1.set_ylabel('relative error')
ax1.set_xlabel('log10(mesh size)')
ax1.set_title('Test of Numerical Derivatives using exp(-x)')

# axes ranges
ax1.set_xlim([-10,-1])
ax1.set_ylim([-12,0])

# the actual plot of the data (column 2 vs column 1, but zero-based)
ax1.scatter(derivative_data[:,0],derivative_data[:,1],c='r',label='forward difference')

# for the fit lines we have to generate a bunch of x values first
x=np.linspace(-10,-1,50)
ax1.plot(x, linear_fit_coefficients[0]*x+linear_fit_coefficients[1],c='b',label=fit_title)

# show the legend
ax1.legend(loc='upper left')

# make sure the plot show up
plt.show()


# Save the figure as a jpeg image

# In[9]:


fig.savefig('derivative_test_python.jpg')


# In[ ]:




