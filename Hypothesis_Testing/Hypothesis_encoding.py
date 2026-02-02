# -*- coding: utf-8 -*-
"""Created by : Kaushik Kumar Umar 
 Date: 02/02/2026

"""



from scipy.stats import norm
import math
mean = 485
var = 500
n=36
sigma = 60
z_value_1 = norm.ppf(0.95)
print(z_value_1)
deviation = z_value_1*sigma/math.sqrt(n)
upper_critical_value = var + deviation
lower_critical_value = var - deviation
if(mean >= lower_critical_value and mean <= upper_critical_value):
  print("Sample mean lies inside the critical range.Conclusion=Fail to reject H0")
else:
  print("Sample mean lies outside the critical range.Conclusion=Reject H0")
