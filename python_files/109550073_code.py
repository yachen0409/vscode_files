import json
import urllib.request
import hmac
import base64
import re
from hashlib import sha1
from wsgiref.handlers  import format_date_time
from datetime import datetime
from time import mktime
from bs4 import BeautifulSoup

PTX_app_id = "PTX_API_ID"
PTX_app_key = "PTX_API_KEY"
GOOGLE_api_key = "GOOGLE_API_KEY"
dorm_place_id = {
    "竹軒" : {
        "lat": 24.789328324503344,
        "lng": 120.99808260663961
    },
    "女二舍" : {
        "lat": 24.784657730611933,
        "lng": 120.99930443741847
    },
    "研三舍" : {
        "lat": 24.783927538389225,
        "lng": 120.99739620001306
    },
    "研二舍" : {
        "lat": 24.7847764101487,
        "lng": 120.99535031393597
    },
    "研一舍" : {
        "lat": 24.789766787862654,
        "lng": 120.99744777106247
    },
    "十三舍" : {
        "lat": 24.783983078127612,
        "lng": 120.99626366317207
    },
    "十二舍" : {
        "lat": 24.78444716200019,
        "lng": 120.9957058361147
    },
    "十一舍" : {
        "lat": 24.790096951572533,
        "lng": 120.99741648145478
    },
    "十舍" : {
        "lat": 24.790146481209632,
        "lng": 120.99669045257143
    },
    "九舍" : {
        "lat": 24.78979977333462,
        "lng": 120.99672402616142
    },
    "八舍" : {
        "lat": 24.78529039706132,
        "lng": 120.99952172335338
    },
    "七舍" : {
        "lat": 24.785568087744245,
        "lng": 120.99939268622943
    }
}
station_info = {
    "YouBike 交通大學(大學路)" : {
        "ID" : "6131",
        "available": 0,
        "location":{
            "lat": 24.789354083219596,
            "lng": 121.00024234741394
        }
    },
    "YouBike 交通大學(逐風廣場)" :{
        "ID" : "6135",
        "available": 0,
        "location":{
            "lat": 24.784726881382717,
            "lng": 120.99987093155798
        }
    },
    "YouBike 交通大學 (研三舍)" :{
        "ID" : "6147",
        "available": 0,
        "location":{
            "lat": 24.784252945477334,
            "lng": 120.99690413390084
        }
    },
    "YouBike 交通大學(新安路)" : {
        "ID" : "9609",
        "available": 0,
        "location":{
            "lat": 24.784162356503572,
            "lng": 120.99356266801794
        }
    }
}
destination = {
    "NTHU_bus_stop":{
        "lat" : 24.79570585552572,
        "lng" : 120.99805252378253
    },
    "NTHU_youbike":{
        "lat" : 24.79684399893586,
        "lng" : 120.99659721457814
    }
}
bus_info = {
    "1822":{
        "comp":"國光客運",
        "bus_gap":"10~15",
        "sequence": 5,
        "depart":"清華大學站"
    },
    "1728":{
        "comp":"亞聯客運",
        "bus_gap":"15~20",
        "sequence": 5,
        "depart":"清華大學站"
    },
    "2011":{
        "comp":"豪泰客運",
        "bus_gap":"10~15",
        "sequence": 5,
        "depart":"清華大學站"
    },
    "9003":{
        "comp":"新竹客運",
        "bus_gap":"10~15",
        "sequence": 5,
        "depart":"清華大學站"
    },
    "2011C":{
        "comp":"豪泰客運",
        "bus_gap":"30~35",
        "sequence": 4,
        "depart":"交大南大門站"
    }
}
class Auth():
    def __init__(self, app_id, app_key):
        self.app_id = app_id
        self.app_key = app_key

    def get_auth_header(self):
        xdate = format_date_time(mktime(datetime.now().timetuple()))
        hashed = hmac.new(self.app_key.encode('utf8'), ('x-date: ' + xdate).encode('utf8'), sha1)
        signature = base64.b64encode(hashed.digest()).decode()

        authorization = 'hmac username="' + self.app_id + '", ' + \
                        'algorithm="hmac-sha1", ' + \
                        'headers="x-date", ' + \
                        'signature="' + signature + '"'

        return {
            'Authorization': authorization,
            'x-date': format_date_time(mktime(datetime.now().timetuple())),
            'Accept - Encoding': 'gzip'
        }
def call_GOOGLE_api(url):
    req = urllib.request.Request(url)
    with urllib.request.urlopen(req) as response:
        data = response.read()
        data = json.loads(data)

    return data
def call_PTX_api(url):
    a = Auth(PTX_app_id, PTX_app_key)
    req = urllib.request.Request(url, headers= a.get_auth_header())
    with urllib.request.urlopen(req) as response:
        data = response.read()
        data = json.loads(data)
    return data

def bike_info():
    api_data = call_PTX_api("https://ptx.transportdata.tw/MOTC/v2/Bike/Availability/Hsinchu?&$format=JSON")
    # print(api_data)
    for data in api_data:
        if data["StationID"] == "6131":
            station_info["YouBike 交通大學(大學路)"]["available"] = data["AvailableRentBikes"]
        elif data["StationID"] == "6135":
            station_info["YouBike 交通大學(逐風廣場)"]["available"] = data["AvailableRentBikes"]
        elif data["StationID"] == "6147":
            station_info["YouBike 交通大學 (研三舍)"]["available"] = data["AvailableRentBikes"]
        elif data["StationID"] == "9609":
            station_info["YouBike 交通大學(新安路)"]["available"] = data["AvailableRentBikes"]
def search_nearby_youbike(location):
    nearby_youbike_station_name = []

    nearby_search_url = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location={},{}&language=zh-TW&radius=50&keyword=bike&key={}".format(location["lat"], location["lng"], GOOGLE_api_key)
    api_data = call_GOOGLE_api(nearby_search_url)

    try:
        nearby_youbike_station_name.append(api_data["results"][0]["name"])
    except:
        nearby_youbike_station_name.append("No_YouBike_nearby")

    for name in nearby_youbike_station_name:
        if name == "YouBike 交通大學 (研三舍)":
            nearby_youbike_station_name.append("YouBike 交通大學(新安路)")
        else:
            continue

    return nearby_youbike_station_name
def map_api(start_location, mid_point, way):
    # print(mid_point)
    traf_mode = ""
    mid_point_destination = destination["NTHU_youbike"]
    route_destination = destination["NTHU_bus_stop"]
    if mid_point.get("lat") == None:
        if way == "騎腳踏車" or way == "youbike":
            traf_mode = "bicycling"
        else:
            traf_mode = "walking"
        # print(traf_mode)
        map_url = "https://maps.googleapis.com/maps/api/distancematrix/json?units=metric&origins={},{}&destinations={},{}&mode={}&language=zh-TW&key={}".format(start_location["lat"], start_location["lng"], route_destination["lat"], route_destination["lng"], traf_mode, GOOGLE_api_key)
        api_data = call_GOOGLE_api(map_url)
        print(api_data)
        time:int = api_data["rows"][0]["elements"][0]["duration"]["value"]
        time = time / 60
        return time
    else:
        time = 0.0
        map_url_rent = "https://maps.googleapis.com/maps/api/distancematrix/json?units=metric&origins={},{}&destinations={},{}&mode=walking&language=zh-TW&key={}".format(start_location["lat"], start_location["lng"], mid_point["lat"], mid_point["lng"], GOOGLE_api_key)
        data_rent_youbike = call_GOOGLE_api(map_url_rent)
        time += data_rent_youbike["rows"][0]["elements"][0]["duration"]["value"]
        # print(time)
        map_url_return = "https://maps.googleapis.com/maps/api/distancematrix/json?units=metric&origins={},{}&destinations={},{}&mode=bicycling&language=zh-TW&key={}".format(mid_point["lat"], mid_point["lng"], mid_point_destination["lat"], mid_point_destination["lng"], GOOGLE_api_key)
        data_return_youbike = call_GOOGLE_api(map_url_return)
        time += data_return_youbike["rows"][0]["elements"][0]["duration"]["value"]
        # print(time)
        map_url_bus_stop = "https://maps.googleapis.com/maps/api/distancematrix/json?units=metric&origins={},{}&destinations={},{}&mode=walking&language=zh-TW&key={}".format(mid_point_destination["lat"], mid_point_destination["lng"], route_destination["lat"], route_destination["lng"], GOOGLE_api_key)
        data_to_bus_stop = call_GOOGLE_api(map_url_bus_stop)
        time += data_to_bus_stop["rows"][0]["elements"][0]["duration"]["value"]
        # print(time)
        time = time / 60
        return time

def yalanbus_fare():
    fare = []
    tickettype = ["全票","半票","亞聯優惠卡","學生票"]
    time = 0
    print("1728亞聯客運 票價資訊:")
    url = "http://www.yalanbus.com.tw/price.htm"
    html = urllib.request.urlopen(url).read()
    soup = BeautifulSoup(html, "html.parser")
    result1 = soup.find_all("p", style="margin-top: 6px; margin-bottom: 6px")
    for item in result1:
        temp = item.get_text()
        compiled_result = re.search(r'(\$.*)',temp)
        if compiled_result != None:
            time += 1
            if time % 3 == 0 and time<=12:
                fare.append(compiled_result.group(1))
    for i in range(0, len(fare)):
        print("{} --> {}".format(tickettype[i], fare[i]))
def hsinchubus_fare():
    tickettype = []
    fare = []
    print("9003新竹客運 票價資訊:")
    url = "http://www.hcbus.com.tw/inquery/1510.htm"
    html = urllib.request.urlopen(url).read()
    soup = BeautifulSoup(html, "html.parser")
    result1 = soup.find_all("td", {"class":["xl34","xl32"]})
    result2 = soup.find_all("td", class_="xl33")
    for item in result1:
        temp = item.get_text()
        if "\xa0" in temp:
            temp = temp.replace("\xa0","")
        if "\r" in temp:
            temp = temp.replace("\r","")
        if "\n" in temp:
            temp = temp.replace("\n","")
        if " " in temp:
            temp = temp.replace(" ","")
        tickettype.append(temp)
    for item in result2:
        temp = item.get_text()
        if "\xa0" in temp:
            temp = temp.replace("\xa0","")
        if "\r" in temp:
            temp = temp.replace("\r","")
        if "\n" in temp:
            temp = temp.replace("\n","")
        if "\u3000" in temp:
            temp = temp.replace("\u3000","")
        if " " in temp:
            temp = temp.replace(" ","")
        fare.append(temp)
    for i in range(0, len(fare)):
        print("{} --> {}".format(tickettype[i], fare[i]))
def get_bus_fare(comp):
    kingbus_fare = {
            "全票" : "135元",
            "半票" : "75元",
            "學生票" : "105元",
            "來回票" : "260元",
            "回數票(8張)":"880元",
            "定期票(40張)":"4000元"
        }
    howtai_fare = {
            "全票" : "140元",
            "半票" : "77元",
            "學生票" : "110元",
            "來回票" : "250元",
            "回數票(10張)":"1150元",
            "定期票(40張)":"4000元"
        }
    if comp == "1":
        print("1822國光客運 票價資訊:")
        for key, value in kingbus_fare.items():
            print("{} --> {}".format(key, value))
    elif comp == "2":
        yalanbus_fare()
    elif comp == "3":
        print("2011豪泰客運 票價資訊:")
        for key, value in howtai_fare.items():
            print("{} --> {}".format(key, value))
    elif comp == "4":
        hsinchubus_fare()
    elif comp == "0":
        print("1822國光客運 票價資訊:")
        for key, value in kingbus_fare.items():
            print("{} --> {}".format(key, value))
        print("")
        yalanbus_fare()
        print("")
        print("2011豪泰客運 票價資訊:")
        for key, value in howtai_fare.items():
            print("{} --> {}".format(key, value))
        print("")
        hsinchubus_fare()
    print("")
    print("2011C豪泰客運 票價資訊:")
    howtai2011c_fare = {
        "全票" : "150元",
        "半票" : "79元",
        "南大門優惠票" : "120元",
        "回數票(10張)":"1300元"
    }
    for key, value in howtai2011c_fare.items():
        print("{} --> {}".format(key, value))
    print("--------------------------------------------------------------------")
def get_bus_info(route_num):
    api_data_final = []
    datanum = enter_time = update_time = 0
    temp_plate = ""
    estimate_time = 0.0
    if route_num == "2011C":
        subroute = route_num + "2"
        api_data = call_PTX_api("https://ptx.transportdata.tw/MOTC/v2/Bus/EstimatedTimeOfArrival/InterCity/2011?$format=JSON")
    else:
        subroute = route_num + "02"
        api_data = call_PTX_api("https://ptx.transportdata.tw/MOTC/v2/Bus/EstimatedTimeOfArrival/InterCity/{}?$format=JSON".format(route_num))

    for data in api_data:
        if data["PlateNumb"] == "-1":
            api_data.remove(data)
        elif data["SubRouteID"] == subroute and data["StopSequence"] <= bus_info[route_num]["sequence"]:
            api_data_final.append(data)
            # print(data)
        update_time = data["UpdateTime"]
    # print(api_data_final)
    if len(api_data_final) == 0:
        print("Oops! {} 在 {} 近{}分鐘內無班次發車:(((".format(route_num+bus_info[route_num]["comp"], bus_info[route_num]["depart"], bus_info[route_num]["bus_gap"]))
        estimate_time = 0
    else:
        for data in api_data_final:
            datanum += 1
            if datanum == 1:
                temp_plate = data["PlateNumb"]
            if data["StopName"]["Zh_tw"] == "清華大學" or "交通大學南大門站":
                enter_time += 1
                if enter_time == 1:
                    estimate_time:float = data["EstimateTime"] / 60
                    print("往台北的 {} 預計 {:.2f} 分鐘後到達{}!".format(route_num+bus_info[route_num]["comp"], estimate_time, bus_info[route_num]["depart"]))
            elif datanum == 1:
                enter_time += 1
                print("往台北的 {} 在距離{}的 {} 站前!".format(route_num+bus_info[route_num]["comp"], bus_info[route_num]["depart"], data["StopCountDown"]))
            elif len(api_data_final) > 1:
                if data["PlateNumb"] != temp_plate:
                    print("再下一班 {} 在距離{}的 {} 站前!".format(route_num+bus_info[route_num]["comp"], bus_info[route_num]["depart"], data["StopCountDown"]))
                    temp_plate = data["PlateNumb"]
    print("(資料更新時間:{})".format(update_time))

    return route_num, estimate_time
def bus_api_2011c():
    print("國道客運交大南大門站即時到站資訊:")
    route_num, estimatetime_2011c = get_bus_info("2011C")
    return route_num, estimatetime_2011c
def bus_api(comp):
    estimatetime = [0,0,0,0,0]
    print("國道客運清大客運站預計到站資訊:")
    if comp == "1":
        route_num, estimatetime[1] = get_bus_info("1822")
    elif comp == "2":
        route_num, estimatetime[2] = get_bus_info("1728")
    elif comp == "3":
        route_num, estimatetime[3] = get_bus_info("2011")
    elif comp == "4":
        route_num, estimatetime[4] =  get_bus_info("9003")
    elif comp == "0":
        route_num, estimatetime[1] = get_bus_info("1822")
        route_num, estimatetime[2] = get_bus_info("1728")
        route_num, estimatetime[3] = get_bus_info("2011")
        route_num, estimatetime[4] = get_bus_info("9003")
        route_num = "no_preference"
    print("")
    route_num2011c, estimatetime_2011c = bus_api_2011c()
    print("")
    while True:
        fare_or_not = input("Step1-1, 請問您需要票價資訊嗎?(Yes/No):").lower()
        if fare_or_not == "yes":
            print("----------------------------Loading----------------------------------")
            get_bus_fare(comp)
            break
        elif fare_or_not == "no":
            break
        else:
            print("Oops! Invalid Input, 請確認您輸入的資料是否有誤或不在選項中:)")

    return route_num, estimatetime, route_num2011c, estimatetime_2011c

def final():
    youbike_station = False
    available_station_count = 0
    choosed_station = 0
    mid_point = {}
    start_location = ""
    print("------------------------------------------------------------------")
    print("---------------------- 歡迎使用交大交通神器!! ----------------------")
    print("------------------------------------------------------------------")
    print("-----本程式能帶您得知往台北的國道客運在清大客運站的及時到站資訊--------")
    print("---並預計您到清大客運站的交通時間，也能查詢出發點附近的Youbike服務-----")
    print("--------同時，本程式也會顯示交大南大門豪泰客運的即時到站資訊-----------")
    print("-------------讓您能在比較後輕鬆規劃搭客運回台北的計劃!----------------")
    print("------------------------------------------------------------------")
    print("")
    print("----------------------!!!!Warning!!!!-----------------------------")
    print("------------請您在程式要求您輸入時輸入\"括號內的選項\"---------------")
    print("------------------要不然會出現Invalid Input!-----------------------")
    print("----------------------!!!!Warning!!!!-----------------------------")
    print("")
    while True:
        bus_comp = input("Step 1, 請輸入您的客運業者偏好(國光、亞聯、豪泰、竹客、無): ")
        if bus_comp == "無":
            bus_comp = "0"
            break
        elif bus_comp == "國光":
            bus_comp = "1"
            break
        elif bus_comp == "亞聯":
            bus_comp = "2"
            break
        elif bus_comp == "豪泰":
            bus_comp = "3"
            break
        elif bus_comp == "竹客":
            bus_comp = "4"
            break
        else:
            print("Oops! Invalid Input, 請確認您輸入的資料是否有誤或不在選項中:)")

    print("----------------------------Loading----------------------------------")
    route_num, estimatetime, route_num2011c, estimatetime_2011c = bus_api(bus_comp)

    match = False
    while True:
        depart = input("Step 2, 請輸入您的出發地點(交大的宿舍名稱):　")
        for key, value in dorm_place_id.items():
            if depart == key:
                start_location = value
                match = True
                break
        if match:
            break
        else:
            print("Oops! Invalid Input, 請確認您輸入的資料是否有誤或不在選項中:)")
    while True:
        traf_way = input("Step 3, 請輸入您前往客運站的交通方式(走路、騎腳踏車): ")
        if traf_way == "騎腳踏車":
            while True:
                youbike_or_not = input("Step 3-1, 請問你想租YouBike嗎?(Yes/No): ").lower()
                if youbike_or_not == "yes":
                    traf_way = "youbike"
                    break
                elif youbike_or_not == "no":
                    traf_way = "騎腳踏車"
                    break
                else:
                    print("Oops! Invalid Input, 請確認您輸入的資料是否有誤或不在選項中:)")
            break
        elif traf_way == "走路":
            break
        else:
            print("Oops! Invalid Input, 請確認您輸入的資料是否有誤或不在選項中:)")

    if traf_way == "youbike":
        print("----------------------------Loading----------------------------------")
        print("")
        bike_info()
        nearby_youbike_station_name = search_nearby_youbike(start_location)
        # print(nearby_youbike_station_name)
        for name in nearby_youbike_station_name:
            if name != "No_YouBike_nearby":
                youbike_station = True
                for station_name, info in station_info.items():
                    # print(station_name)
                    if station_name == name:
                        if info["available"] > 0:
                            available_station_count += 1
                        else:
                            nearby_youbike_station_name.remove(name)
            else:
                traf_way = "走路"
                print("附近連YouBike站都沒有......走路吧QAQ")
                print("正在估算您從起點 走路 到清大客運站的預計時間......")

        if youbike_station:
            if available_station_count > 1:
                messege = """附近有 {} 個YouBike站有可以借的腳踏車! 你想要去哪個YouBike站借腳踏車呢?
 ---------------------------------------------------------------
    1. {: ^20} -->剩下{: ^4}台車可以借!
    2. {: ^20} -->剩下{: ^4}台車可以借!
 ---------------------------------------------------------------""".format(available_station_count, nearby_youbike_station_name[0], station_info[nearby_youbike_station_name[0]]["available"], nearby_youbike_station_name[1], station_info[nearby_youbike_station_name[1]]["available"])
                print(messege)
                while True:
                    choosed_station = input("請輸入相應的數字代號: ")
                    if choosed_station == "1":
                        mid_point = station_info[nearby_youbike_station_name[0]]["location"]
                        break
                    elif choosed_station == "2":
                        mid_point = station_info[nearby_youbike_station_name[1]]["location"]
                        break
                    else:
                        print("Oops! Invalid Input, 請確認您輸入的資料是否有誤或不在選項中:)")
            elif available_station_count == 1:
                print("附近的 {} 剩下 {} 臺車可以借!".format(nearby_youbike_station_name[0], station_info[nearby_youbike_station_name[0]]["available"]))
                print("")
                mid_point = station_info[nearby_youbike_station_name[0]]["location"]
            else:
                print("Oops! 附近的YouBike站都無車可借QAQ......")
                print("正在估算假設您有腳踏車 騎腳踏車 從起點清大客運站的預計時間......")
                print("")
    print("----------------------------Loading----------------------------------")
    time = map_api(start_location, mid_point, traf_way)
    print("")
    print("Results:")
    print("----------------------------------------------------------------------------")
    print("{} 從 {} 到清大客運站須時大約 {:.2f} 分鐘:)))".format(traf_way, depart, time))
    print("----------------------------------------------------------------------------")
    print("")

    if route_num == "no_preference":
        route_num = ["1822","1728","2011","9003"]
        for i in range(1, 5):
            if estimatetime[i] < time:
                print("Oops! 就算立即出發，你也趕不上 {} 最近的一班車:(((".format(route_num[i-1]+bus_info[route_num[i-1]]["comp"]))
                print("建議您搭乘下一班 {} 後出發的 {}!".format(bus_info[route_num[i-1]]["bus_gap"], route_num[i-1]+bus_info[route_num[i-1]]["comp"]))
            elif estimatetime[i] >= time:
                print("--> 欸 有機會ㄟ!!!!!<--")
                print("若您想搭到 {} 最快出發的一班車，您應該在 {:.2f} 分鐘內出發!".format(route_num[i-1]+bus_info[route_num[i-1]]["comp"], estimatetime[i]-time))
            print("")
    else:
        if estimatetime[int(bus_comp)] < time:
            print("Oops! 就算立即出發，你也趕不上 {} 最近的一班車:(((".format(route_num+bus_info[route_num]["comp"]))
            print("建議您搭乘下一班 {} 後出發的 {}!".format(bus_info[route_num]["bus_gap"], route_num+bus_info[route_num]["comp"]))
        elif estimatetime[int(bus_comp)] >= time:
            print("若您想搭到 {} 最快出發的一班車，您應該在 {:.2f} 分鐘內出發!".format(route_num+bus_info[route_num]["comp"], estimatetime[i]-time))
        print("")
    if estimatetime_2011c < 5.0:
        print("另外，您也可以選擇搭乘交大校內的 {} ，預計於 {} 分鐘後出發:))))".format(route_num2011c+bus_info[route_num2011c]["comp"], bus_info[route_num2011c]["bus_gap"]))
    else:
        print("另外，您也可以選擇搭乘交大校內的 {} ，預計於 {:.2f} 分鐘後出發:))))".format(route_num2011c+bus_info[route_num2011c]["comp"], estimatetime_2011c))
    print("")
    print("----------------------------------------------------------------------------")
    print("---------------------------End of Program, 謝謝使用!-------------------------")
    print("----------------------------------------------------------------------------")
if __name__ == "__main__":
    final()