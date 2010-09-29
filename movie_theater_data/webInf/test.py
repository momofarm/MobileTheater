import web
from web import utils

from data_retrive import GetIDs, GetTheaterInfo, GetAreas, GetNearFiveLocation

urls = ("/bb", "hello",
	"/test", "test",
	"/test2/(.*)", "test2",
	"/dbTest", "dbTest",
	"/list/(.*)", "theaterList",
	"/info/(.*)", "theaterInfo",
	"/areas", "areas", 
	"/loc/(.*)", "loc")

#web.header("Content-Type", "text/html; charset= utf-8")

app = web.application(urls, globals())

db = web.database(dbn = 'mysql',
			user = '',
			pw = '',
			db = 'movie_time')

db.query('SET NAMES \'utf8\';')


class hello:
    def GET(self):
        return 'Hello, world!'

class test:
	def GET(self):
		return "Test"

class test2:
	def GET(self, argv):
		print 'argv is %s' % argv
		render = web.template.render('template/')		
		#name = 'bob'
		i = web.input(name=None)
		print i
		return render.test(argv)

	def POST(self):
		pass


class dbTest:
	def GET(self):
		#web.header("Content-Type", "text/html; charset= utf-8") 
	
		name = db.select('THEATER')
		
		render = web.template.render('template/')		
	
		from web import utils
		
		print name[0].NAME
	
		return render.dbtest(name)

		
	def POST(self):
		pass



class theaterList:
	def GET(self, area):
		#print 'argv is %s' % argv
		web.header("Content-Type", "text/html; charset= utf-8")
	
		render = web.template.render('template/')		
	
		#i = web.input(name=None)

		whereExpr = "PART_AREA = \"%s\"" % area
	
		print whereExpr

		whereExprText = unicode(whereExpr).encode('utf-8')

		print whereExprText
		
		data = db.select('THEATER', where = whereExpr)
				
		text = GetIDs(data)
							
		return render.arealist(text)


class theaterInfo:
	def GET(self, ID):
		web.header("Content-Type", "text/html; charset= utf-8")
	
		render = web.template.render('template/')		
	
		#i = web.input(name=None)

		"""section 1: get theater info from theater table"""

		expr = "THEATER_ID = \"%s\"" % ID
	
		data = db.select('THEATER', where = expr)
	
		"""section 2: get time data from theater_time table"""
		data2 = db.select('THEATER_TIME', where = expr)		

		"""final section: merge to function and get json formed data back"""
	
		text = GetTheaterInfo(data, data2)
						
		return render.arealist(text)

class areas:
	def GET(self):
		web.header("Content-Type", "text/html; charset= utf-8")
	
		render = web.template.render('template/')		

		data = db.select('AREAS')
	
		text = GetAreas(data)		 					
	
		return render.arealist(text)

		
class loc:
	def GET(self, gpsValue):
		web.header("Content-Type", "text/html; charset= utf-8")
	
		render = web.template.render('template/')		
	
		values = gpsValue.split(',')
		
		location_data = db.select('THEATER')

		aryData = []
		

		for d in location_data:
			distance = 0
			aryData.append([d.THEATER_ID, d.GPS, distance, d.NAME])
							
		text = GetNearFiveLocation(values[0], values[1], aryData)

		
		return render.arealist(text)
		

if __name__ == "__main__":
    app.run()

