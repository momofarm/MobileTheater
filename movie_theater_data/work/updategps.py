
#!/usr/bin/python
#-*-coding:utf-8-*-

import sys
reload(sys)
sys.setdefaultencoding('utf8')

from db_maintain import DB_Maintain
d = DB_Maintain()

for id in range(90, 103):
	testID = "T%05d" % id	
	d.UpdateGPS(testID)

