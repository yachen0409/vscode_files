import os
import tornado.ioloop
import tornado.web
import tornado.template
import tornado.log

import hashlib
import random

import pickle
import atexit

''' Global Variables
function use and answer checking
'''
LETTERS_FOR_PASSWORDS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345678901234567890123456789'
LETTERS_FOR_KEYS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'

key_dic = {}
pw_dic = {}
cipher_dic = {}
rail_text = ""
lv1_whole = ""
lv1_answer = {}
lv1_qiz_dic = {}
lv1_ans_dic = {}

'''Level 1 fucntions
genRadNum():
    1. Generate Rail Cipher for Level 1 text
    2. Store value for information showing.
encryptRailFence():
    1. Return Rail Fence Cipher
'''
def genRadNum():
    global rail_text, lv1_answer, lv1_whole, lv1_ans_dic, lv1_qiz_dic
    for i in range(16):
        bob_buy = random.randint(2, 20)
        duckie_usd = random.randint(1, 20)
        usd_tw = random.randint(20, 50)
        duckie_usd_after = random.randint(100, 200)
        usd_tw_after = random.randint(1, 50)
        rail_key = random.randint(2, 5)

        text = "Alice and Bob are talking about their opinion about Duckiecoin, since Duckiecoin is a kind of cryptocurrencies, since the exchange rate is very unstable,so it is very risky to take cryptocurrencies as an investment. One day, Bob buy " + str(bob_buy) + " Duckiecoins secretly at " + str(duckie_usd) + " USD, when 1 USD = " + str(usd_tw) + " TWD. Few months ago, his wife, Alice, finds that Bob owns some cryptocurrency and ask Bob to sell them all, the exchange rate now is 1 Duckiecoin = " + str(duckie_usd_after) + " USD, 1 USD = " + str(usd_tw_after) + " TWD, please help Bob calculate the profit(or loss) that he can get."
        text = encryptRailFence(text, rail_key).replace(" ", "&ensp;")
        rail_text = f"{text}"

        lv1_answer[f"group{i}"] = bob_buy * (duckie_usd_after * usd_tw_after - duckie_usd * usd_tw)

        lv1_whole = f'''
        <ul>
            <caption><p style="background: aqua;">Level1 Question (group{i})</p></caption>
            <li>
                <p>{rail_text}</p>
            </li>
            <li>Rail Key: {rail_key}</li>
        </ul>
        <ol>
            <caption><p style="background: aqua;">Level1 Answer (group{i})</p></caption>
            <li>{lv1_answer[f"group{i}"]}</li>
            <li>bob buy: {bob_buy}</li>
            <li>bit usd: {duckie_usd}</li>
            <li>usd tw: {usd_tw}</li>
            <li>bit usd after: {duckie_usd_after}</li>
            <li>usd tw after: {usd_tw_after}</li>
        </ol>
        '''

        lv1_qiz_dic[f"group{i}"] = rail_text
        lv1_ans_dic[f"group{i}"] = lv1_whole


def encryptRailFence(text, key):
    rail = [['\n' for i in range(len(text))]
                for j in range(key)]

    dir_down = False
    row, col = 0, 0

    for i in range(len(text)):
        if (row == 0) or (row == key - 1):
            dir_down = not dir_down
        rail[row][col] = text[i]
        col += 1
        if dir_down:
            row += 1
        else:
            row -= 1
    result = []
    for i in range(key):
        for j in range(len(text)):
            if rail[i][j] != '\n':
                result.append(rail[i][j])
    return("" . join(result))    
    

''' Level 2 functions
'''
def getRandomPassword(key: str):
    randomList = list(LETTERS_FOR_PASSWORDS)
    random.shuffle(randomList)
    store: str = ''.join(str(e) for e in randomList)
    if pw_dic.get(key) == None:
        pw_dic[key] = store[:8]
    return store


def getRandomKey(key: str):
    randomList = list(LETTERS_FOR_KEYS)
    random.shuffle(randomList)
    store: str = ''.join(randomList)
    if key_dic.get(key) == None:
        key_dic[key] = store
    return store

def getCipher(message, key):
    cipher = ''
    charsA = LETTERS_FOR_KEYS
    charsB = key
    for symbol in message:
        if symbol in charsA:
            symIndex = charsA.find(symbol)
            cipher += charsB[symIndex]
        else:
            cipher += symbol
    return cipher

def string2bi(str1):
    s = ''
    for ch in str1:
        if(ch == "\n"):
            s += "\n"
        else:
            if(ord(ch)<64):
                s += "0"
            for c in ch:
                s += bin(ord(c)).replace('b','')
            s += " "
          
    return s


'''Handler
PwKeyRestoreHandler:
    - Showing all information for TA
LevelRailHandler:
    - level 1 handler
Level2Handler:
    - level 2 handler
PassShowHandler:
    - Not exist in routing table, use for dumpong file
Level1Handler:
    - abandoned
'''

# Handler for showing Passwd and Key
class PwKeyRestoreHandler(tornado.web.RequestHandler):
    level1_pass = {
        f"group{gid}": False
        for gid in range(16)
    }
    level2_pass = {
        f"group{gid}": False
        for gid in range(16)
    }
    genRadNum()
    # try to restore
    try:
        level1_pass, level2_pass = pickle.load(open('./pass.pickle', "rb"))
    except FileNotFoundError:
        pass

    def get(self):
        rtn = "<h1>Answer Management</h1>"
        for group, key in key_dic.items():
            rtn += f'''
                    <h2>
                        <section style="border: white dotted 5px;">{group}<section>
                    </h2>
                    '''
            rtn += f'''
                    {lv1_ans_dic[group]}
                    '''
            rtn += f'''<ol>\
                        <caption><p style="background: yellow">Level2 Info ({group})<p></caption>\
                        <li>Key:{key}</li>\
                        <li>Passwd: {pw_dic[group]} </li>\
                        <li>Content: {cipher_dic.get(group)}</li>\
                        <li>level1: {repr(self.level1_pass[group])}</li>\
                        <li>level2: {repr(self.level2_pass[group])}</li>\
                    </ol>'''
            rtn += f'''<ul>\
                        <caption><p style="background: yellow">Level2 Cipher ({group})<p></caption>\
                        <li>Binary Key: {string2bi(key)}</li>\
                        <li>Binary Content: {string2bi(cipher_dic.get(group))}</li>\
                    </ul>'''
        return self.write(
            f"{rtn}"
        )


# Level 1 Handler
class LevelRailHandler(tornado.web.RequestHandler):
    shadow = {
        f"group{gid}": lv1_answer[f"group{gid}"]
        for gid in range(16)
    }
    def get(self, group_name: str, *path_args, **path_kwargs):
        self.write(
            rail_page.generate(
                content=lv1_qiz_dic[group_name], 
                group_name=group_name
            )
        )
        return

    def post(self, group_name: str, *path_args, **path_kwargs):
        submitter = self.request.body_arguments['group_name'][0]
        answer = self.request.body_arguments['answer'][0]
        ans = self.shadow.get(group_name, None)
        if (
            int(ans) == int(answer.decode('utf-8')) and
            group_name == submitter.decode('utf-8')
        ):
            self.write(f'{group_name} pass level 1 !!!')
            print(f"~~~~Success~~~~\n{group_name} pass level 1.")
            if not PassShowHandler.level1_pass[group_name]:
                PassShowHandler.level1_pass[group_name] = (
                    True, str(datetime.datetime.now()),
                )
            if not PwKeyRestoreHandler.level1_pass[group_name]:
                PwKeyRestoreHandler.level1_pass[group_name] = (
                    True, str(datetime.datetime.now()),
                )
            return
        else:
            self.write(
                f"Seems not good enough ? "
            )
            print("~~~~Fail Log~~~~")
            if int(ans) != int(answer.decode('utf-8')):
                print(f"{group_name} fail to pass answer")
            elif group_name == submitter.decode('utf-8'):
                print(f"{group_name} has wrong user name")
        return

# Show If pass
class PassShowHandler(tornado.web.RequestHandler):
    level1_pass = {
        f"group{gid}": False
        for gid in range(16)
    }
    level2_pass = {
        f"group{gid}": False
        for gid in range(16)
    }
    # try to restore
    try:
        level1_pass, level2_pass = pickle.load(open('./pass.pickle', "rb"))
    except FileNotFoundError:
        pass

    def get(self):
        return self.write(
            f'level1: {repr(self.level1_pass)}<br />level2: {repr(self.level2_pass)}'
        )

    atexit.register(
        lambda: pickle.dump(
            tuple([
                PassShowHandler.level1_pass,
                PassShowHandler.level2_pass,
            ]),
            open('./pass.pickle', "wb"),
        ),
    )

class Level2Handler(tornado.web.RequestHandler):
    default_tmpl_var = {
        'answer': None,
        'error_msg': '',
        'level': 2,
        'level_info': "",
    }
    shadow = {
        f"group{gid}": getRandomPassword(f"group{gid}")[:8]
        for gid in range(16)
    }
    udp_port = {
        f"group{gid}": int(54766 + gid)
        for gid in range(16)
    }
    pass_level = {
        f"group{gid}": False
        for gid in range(16)
    }

    def get_level_info(self, group_name: str):
        p = self.udp_port.get(group_name, None)
        return f'please sniffer Alice and Bob UDP packet at {p}. to find the password'

    def get(self, group_name: str, *path_args, **path_kwargs):
        # set level info
        self.write(
            login_page.generate(group_name=group_name, **{
                **self.default_tmpl_var,
                'level_info': self.get_level_info(group_name),
            })
        )
        return

    def post(self, group_name: str, *path_args, **path_kwargs):
        # set level info

        duckie = self.request.body_arguments['duckie'][0]
        duckieduckie = self.request.body_arguments['duckieduckie'][0]

        tmpl_var = {
            'error_msg': []
        }

        real_duckieduckie = self.shadow.get(group_name, None)

        if (
            real_duckieduckie == duckieduckie.decode('utf-8')
            and group_name == duckie.decode('utf-8')
        ):
            tmpl_var['error_msg'].append('Pass !!!')
            self.write(f'{group_name} pass level 2 !!!')
            print(f"""~~~~Success~~~~\n{group_name} pass level2""")
            if not PassShowHandler.level2_pass[group_name]:
                PassShowHandler.level2_pass[group_name] = (
                    True, str(datetime.datetime.now()),
                )
            if not PwKeyRestoreHandler.level2_pass[group_name]:
                PwKeyRestoreHandler.level2_pass[group_name] = (
                    True, str(datetime.datetime.now()),
                )
            return
        if real_duckieduckie != duckieduckie.decode('utf-8'):
            tmpl_var['error_msg'].append('wrong password')
        if group_name != duckie.decode('utf-8'):
            tmpl_var['error_msg'].append('wrong user')

        tmpl_var['error_msg'] = ", ".join(tmpl_var['error_msg'])

        self.write(login_page.generate(group_name=group_name, **{
            **self.default_tmpl_var,
            **tmpl_var,
            'level_info': self.get_level_info(group_name),
        }))
        return



# # Not using
# class Level1Handler(tornado.web.RequestHandler):
#     default_tmpl_var = {
#         'answer': None,
#         'error_msg': '',
#         'level': 1,
#         'level_info': None,
#     }
#     shadow = {
#         f"group{gid}": hashlib.md5(str(random.random()).encode('utf-8')).hexdigest()[:6]
#         for gid in range(16)
#     }

#     def get(self, group_name: str, *path_args, **path_kwargs):
#         self.write(
#             login_page.generate(group_name=group_name, **self.default_tmpl_var)
#         )
#         return

#     def post(self, group_name: str, *path_args, **path_kwargs):

#         duckie = self.request.body_arguments['duckie'][0]
#         duckieduckie = self.request.body_arguments['duckieduckie'][0]

#         tmpl_var = {
#             'error_msg': []
#         }

#         real_duckieduckie = self.shadow.get(group_name, None)

#         if (
#             real_duckieduckie == duckieduckie.decode('utf-8')
#             and group_name == duckie.decode('utf-8')
#         ):
#             tmpl_var['error_msg'].append('Pass !!!')
#             self.write(f'{group_name} pass level 1 !!!')
#             if not PassShowHandler.level1_pass[group_name]:
#                 PassShowHandler.level1_pass[group_name] = (
#                     True, str(datetime.datetime.now()),
#                 )
#         if real_duckieduckie != duckieduckie.decode('utf-8'):
#             tmpl_var['error_msg'].append('wrong password')
#             tmpl_var['answer'] = real_duckieduckie
#         if group_name != duckie.decode('utf-8'):
#             tmpl_var['error_msg'].append('wrong user')

#         tmpl_var['error_msg'] = ", ".join(tmpl_var['error_msg'])

#         self.write(login_page.generate(group_name=group_name, **{
#             **self.default_tmpl_var,
#             **tmpl_var,
#         }))
#         return




'''Web Page Template
'''
login_page = tornado.template.Template('''
{% if answer %}
<!-- password is {{ answer }} -->
{% end %}
<html>
    <head>
        <meta name="keywords" content="Challenge9 Level 1" />
        <meta charset="utf-8" />
        <title> Ch9 Lv.2 Shhhhhhh !!</title>
        <style>
            #aside-window{
                visibility: hidden;
                position: fixed;
                top: 0;
                right: 0;
            }
            .to-middle{
                margin-left: auto;
                margin-right: auto;
                text-align: center;
                margin-top: 10px;
                margin-bottom: 10px;
            }
            h1{
                text-align: center;
            }
            .login-panel{
                border: aqua outset 5px;
                background-color: bisque;
                margin-left: 40%;
                margin-right: 40%;
            }
            @keyframes blink{
                0%{
                    opacity: 1;
                } 
                50%{
                    opacity: 0;
                } 
                100%{
                    opacity: 1;
                } 
            }
            @-webkit-keyframes blink {
                0%{
                    opacity: 1;
                } 
                50%{
                    opacity: 0;
                } 
                100%{
                    opacity: 1;
                } 
            }
            @-moz-keyframes blink {
                0%{
                    opacity: 1;
                } 
                50%{
                    opacity: 0;
                } 
                100%{
                    opacity: 1;
                } 
            }
            @-ms-keyframes blink {
                0%{
                    opacity: 1;
                } 
                50%{
                    opacity: 0;
                } 
                100%{
                    opacity: 1;
                } 
            }
            @-o-keyframes blink {
                0%{
                    opacity: 1;
                } 
                50%{
                    opacity: 0;
                } 
                100%{
                    opacity: 1;
                } 
            }
            .blink{
                color: gray;
                font-size: 1.5em;
                animation: blink 4s linear infinite;  
                /*capability*/
                -webkit-animation: blink 4s linear infinite;
                -moz-animation: blink 4s linear infinite;
                -ms-animation: blink 4s linear infinite;
                -o-animation: blink 4s linear infinite;
            }
        </style>
    </head>
    <body>
        <script type="text/javascript" >
            function haha(e) {
                console.log(e)
                e.preventDefault()
            }
        </script>
        <h1> Shhhhhhhh !! </h1>
        <div class="to-middle">
            <p class="blink">
            {% if level_info %}
            {{ level_info }}
            </p>
        <div>
        <div class="to-middle">
            {% end %}
            {% if error_msg %}
            <pre> {{ error_msg }} </pre>
            {% end %}
            <form name="login" action="" method="POST" class="login-panel">
                <legend><div style="margin-bottom: 15px;">~~Sneaky Login~~</div></legend>
                <section calss="to-middle">
                <label>User: <input type="text" name="duckie" value="{{ group_name }}" /> </label>
                <br />
                </section>
                <section class="to-middle">
                <label>Password: <input type="password" name="duckieduckie" /> </label>
                <br />
                </section>
                <input type="submit" name="submit" value="login" />
            </form>
        </div>
    </body>
</html>
''')

rail_page = tornado.template.Template('''
<!DOCTYPE html>
<html>
    <head>
        <meta name="keywords" content="Challenge9 Level 1" />
        <meta charset="utf-8" />
        <title> Ch9 Lv.1 Can you solve it ?</title>
        <style>
            #aside-window{
                visibility: hidden;
                position: fixed;
                top: 0;
                right: 0;
            }
            .to-middle{
                margin-left: auto;
                margin-right: auto;
                text-align: center;
                margin-top: 10px;
                margin-bottom: 10px;
            }
            h1{
                text-align: center;
            }
        </style>
        <script>
            function move(){
                var aside = document.getElementById("aside-window");
                if (aside != null){
                    aside.style.top = `${100 + 150 * Math.random()}px`;
                    aside.style.right = `${100 + 200 * Math.random()}px`;
                }
            }
            function QQ(){
                window.alert('Oach!');

                var target = document.getElementById("encrypt"),
                    aside = document.getElementById("aside-window");
                target.innerHTML="Here you are~"
                aside.style.visibility = "visible";
                window.setInterval(move, 200);
            }
            function Hint(select){
                if (select == 1)
                    window.alert("請同學們記得'每一個'空格都要複製到喔~~");
                else if (select == 2)
                    window.alert("順帶一提，助教覺得把題目複製成檔案再讀取會比較方便喔~")
            }
        </script>
    </head>
    <body>
        <h1> Can you solve it ? </h1>
        <article>
            <p class="to-middle">
                今天的Challenge 9 十分的快樂及有趣，<br />
                請活用各位在tutorial 學到的各種知識，<br />
                開開心心的享受Challenge 9 ~~<br />
                以下是題目: ↘↘↘↘↘<font onclick="Hint(1);">⇊</font>⇊⇊<font onclick="QQ();">⇊</font>↙↙↙↙↙
            </p>
            <p class="to-middle" style="padding-left: 20%; padding-right: 20%;">
                {% raw content %}
            </p>
            <div class="to-middle">
                <form name="login" action="" method="POST" >
                    <section class="to-middle">
                    <label>Group <input type="text" name="group_name" value="{{ group_name }}" /></label> <br />
                    </section>
                    <section class="to-middle">
                    <label>Answer <input type="text" name="answer" /></label> <br />
                    </section>
                    <input type="submit" name="submit" value="submit!" />
                </form>
            </div>
            <p class="to-middle">
                相信各位經過了以上↗↗↗↗↗⇈⇈<font onclick="Hint(2)">⇈</font>⇈↖↖↖↖↖簡單的題目測試之後，<br />
                對後面的level2 一定充滿了信心ㄅ，<br />
                那麼，讓我們邁向<a href="/level2/{{ group_name }}">第二關</a>吧。<br />
                (請注意此次challenge 必須按照<font onclick="QQ();">助教提供</font>的表格填寫適當的網址)
            </p>
        </article>
        <aside id="aside-window">
            <a href="https://reurl.cc/Q6lzpO" targe="_blank" id="encrypt">
                Can you find me??
            </a>
        </aside>
    </body>
</html>
''')





import socket
import time
import select
import json
import datetime
import sys
import traceback


def serialize_chat_message(from_: str, to: str, msg: str):
    data = {
        'from': from_,
        'to': to,
        'msg': msg,
    }
    now = datetime.datetime.now()
    data['now'] = now.strftime("%Y-%m-%dT%H:%M:%S")
    return json.dumps(data, ensure_ascii=True).encode('ascii')


def deserialize_chat_message(data: bytes):
    return json.loads(data)


import io
import itertools
import random
import threading


def chatbot(
    port: int, who: str, chat_to: str, iofile: io.StringIO,
    auto_reply: bool = True, auto_reply_first: bool = True,
):
    print(f'chatbot start {who}=>{chat_to} at {port}')
    with socket.socket(type=socket.SOCK_DGRAM) as u:
        u.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, True)
        u.bind(('', port))

        display_before = {}

        reply_round_robin: itertools.cycle = None
        s1: socket.socket = None
        if auto_reply:
            reply_lines = iofile.readlines()
            reply_round_robin = itertools.cycle(reply_lines)
            orig_iofile = iofile
            s1, s2 = socket.socketpair()
            iofile = s2.makefile("r")
            if auto_reply_first:
                reply = next(reply_round_robin)
                s1.send(reply.encode('ascii'))
        auto_reply_timeout: float = 10.0  # sec
        prev_send_time: float = time.time()
        while True:
            if (
                auto_reply
                and (
                    (time.time() - prev_send_time)
                    > auto_reply_timeout
                )
            ):
                reply = next(reply_round_robin)
                s1.send(reply.encode('ascii'))
                # print(f'{who} timeout to reply {chat_to} at {port}')
            readable, _, _ = select.select([u, iofile], [], [], 0.1)
            if len(readable) == 0:
                continue
            if u in readable:
                chat_data, addr = u.recvfrom(65535)
                # parse
                try:
                    chat_msg = deserialize_chat_message(chat_data)
                except BaseException:
                    traceback.print_exc()
                    continue
                # drop it
                if chat_msg['from'] != who and chat_msg['to'] != who:
                    continue
                try:
                    show = "[ {now} ] {from} >> {msg}".format_map(chat_msg)
                    if show not in display_before:
                        if iofile.writable():
                            iofile.write(show)
                        else:
                            if not auto_reply:
                                print(show, end='')
                        if auto_reply and reply_round_robin and chat_msg['from'] != who:
                            reply = next(reply_round_robin)
                            # random wait time to simulate human
                            wait_time: float = 0  # sec
                            # each char read it
                            wait_time += len(chat_msg['msg']) * \
                                (0.1 + 0.3 * random.random())
                            # human thinking
                            wait_time += 1 + 1 * random.random()
                            # human typing
                            wait_time += len(reply) * \
                                (0.1 + 0.3 * random.random())
                            # print(
                            #     f'{who} wait {wait_time} sec to reply {chat_to} at {port}'
                            # )
                            time.sleep(wait_time)
                            s1.send(reply.encode('ascii'))
                    display_before[show] = True
                    if len(display_before) > 100:
                        display_before = {}
                except KeyboardInterrupt:
                    raise
                except BaseException:
                    traceback.print_exc()
                    continue
            if iofile in readable:
                msg = iofile.readline()
                # eof
                if not msg:
                    raise EOFError
                chat_data = serialize_chat_message(
                    from_=who, to=chat_to, msg=msg,
                )
                u.sendto(chat_data, ('<broadcast>', port))
                prev_send_time = time.time()
    pass



def main():
    for gn, p in Level2Handler.udp_port.items():
        real_duckieduckie = Level2Handler.shadow[gn]
        key = getRandomKey(gn)
        words = "Hi Bob!\nI forgot your account\nThanks! Is it " + real_duckieduckie + " ?\n"
        ciphertext = getCipher(words, key)
        bi_key = string2bi(key)
        bi_ciphertext = string2bi(ciphertext)
        if cipher_dic.get(f"{gn}") == None:
            cipher_dic[f"{gn}"] = ciphertext
        t = threading.Thread(
            target=chatbot,
            kwargs=dict(
                port=p,
                who='Alice',
                chat_to='Bob',
                iofile=io.StringIO(f"{bi_key}\n{bi_ciphertext}"),
                auto_reply_first=False,
            ),
            daemon=True,
        )
        t.start()
    app = tornado.web.Application([
        tornado.web.url(r"/level2/(?P<group_name>group\d{1,2})", Level2Handler),
        tornado.web.url(r"/level1/(?P<group_name>group\d{1,2})", LevelRailHandler),
        tornado.web.url(r"/thisIsSecureAndDangerousABCD", PwKeyRestoreHandler)
    ])
    app.listen(os.getenv("PORT", 55555), address="0.0.0.0")
    tornado.log.enable_pretty_logging()
    tornado.ioloop.IOLoop.current().start()


if __name__ == "__main__":
    if len(sys.argv) == 1:
        main()
    else:
        input("start ? ")
        for gn, p in Level2Handler.udp_port.items():
            t = threading.Thread(target=chatbot, kwargs=dict(
                port=p,
                who='Bob',
                chat_to='Alice',
                iofile=io.StringIO(f"Hi Alice!\nWhat? No way\nYes!\n"),
                auto_reply_first=True,
            ), daemon=False)
            t.start()