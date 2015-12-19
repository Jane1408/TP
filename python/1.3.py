# -*- coding: utf8 -*-

import urllib
import urllib2
import re
import os

def name_of_files(name_file):
    name = ''
    if name_file[len(name_file) - 1] == '/':
        name_file = name_file[:len(name_file) - 1]
    for i in range(name_file.rfind('/') + 1, len(name_file)):
        if name_file[i].isalnum() or name_file[i] == '.' or name_file[i] == '_' or name_file[i] == '-':
            name += name_file[i]
    return name

def name_of_folder(name_folder):
    name = ''
    for i in range(0, len(name_folder)):
        if name_folder[i] != '/' and name_folder[i] != ':':
            name += name_folder[i]
    return name

def preserving_the_content_of_the_url(main_url, url, name_directory, main_dir):
    extra_contents = ''
    name_directory = str(name_directory)
    new_dir = main_dir + '\\' + name_directory
    os.mkdir(new_dir)
    os.chdir(new_dir)
    if url.find('http') < 0:
        correct_url = main_url + url
    else:
        correct_url = url
    contents = urllib2.urlopen(correct_url).read()
    img_urls = re.findall('img.*?src="(.*?)"', contents)
    img_urls1 = re.findall('href="(.*?)"', contents)
    js_urls = re.findall('script.*?src=\"(.*?.js)\"', contents)
    js_urls1 = re.findall('link.*?href=\"(.*?.js)\"', contents)
    css_urls = re.findall('link.*?href=\"(.*?.css)\"', contents)
    urls = img_urls + js_urls + css_urls + js_urls1 + img_urls1

    for i in range(len(urls)):
        try:
            address = urls[i]
            if address[address.rfind('.') + 1:] in list_extensions:
                name_file = address[address.rfind('/') + 1:]
                name_file = name_of_files(name_file)
                index = contents.find(address)
                extra_contents = contents[: index] + '/' + new_dir + '/' + name_file + contents[index + len(address):]
                contents = extra_contents
                extra_contents = ''
                if address.find('http') < 0:
                    address = main_url + address
                if address.find('http') > 0:
                    address = address[address.find('http'):]
                urllib.urlretrieve(address, name_file)
        except IOError:
            print 'Error!'
    os.chdir(main_dir)
    file_out = open(str(name_directory) + '.html', 'w')
    file_out.write(contents)
    file_out.close()


list_extensions = ['gif', 'bmp', 'jpg', 'jpeg', 'png', 'js', 'css', 'html', 'ico']
main_dir = os.getcwd()
numb_pages = 100

saved_pages = []

no_mistakes = True

main_url = raw_input('Enter site: ')
word = raw_input('Enter word: ')
name_directory = main_url[main_url.rfind('/') + 1:]
contents = urllib2.urlopen(main_url).read()
urls_list = re.findall('a.*?href="(.*?)"', contents)
i = 0
while (i < len(urls_list)) and (len(saved_pages) <= numb_pages):
    if urls_list[i].find('http') < 0:
        correct_url = main_url + urls_list[i]
    else:
        correct_url = urls_list[i]
    if (urls_list[i].find('@') > 0) or (urls_list[i].find('#') > 0):
        urls_list.pop(i)
        no_mistakes = False
    try:
        contents = urllib2.urlopen(correct_url).read()
    except IOError:
        urls_list.pop(i)
        no_mistakes = False
    if no_mistakes:
        if (contents.find(word) > 0) and (correct_url not in saved_pages) and (len(saved_pages) <= numb_pages) and \
                (correct_url != (main_url + '/rss')):
            try:
                preserving_the_content_of_the_url(main_url, urls_list[i], name_directory, main_dir)
                os.chdir(main_dir)
                name_directory = name_of_folder(urls_list[i])
                saved_pages.append(correct_url)
                if len(urls_list) <= 1000:
                    urls_list += re.findall('a.*?href="(.*?)"', contents)
                urls_list.pop(i)
            except IOError:
                urls_list.pop(i)
        elif (contents.find(word) < 0) and (correct_url not in saved_pages):
            if len(urls_list) <= 1000:
                urls_list += re.findall('a.*?href="(.*?)"', contents)
            urls_list.pop(i)
        elif ((contents.find(word) > 0) and (correct_url in saved_pages)) or (correct_url == (main_url + '/rss')):
            urls_list.pop(i)
    no_mistakes = True
