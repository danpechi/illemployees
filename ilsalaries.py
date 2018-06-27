# Madeleine Schwartz
# June 27th 2018
# ilsalaries.py
# 
# Illinois legislative salary data scraped from Illinois Comptroller 
# employee salary database, and printed as an csv to stdout

# import methods and libraries
import urllib

# # # # # # # # # # # # # #
# Define Helper functions #
# # # # # # # # # # # # # #

# removeSuffix: given a string word and string suffix, 
# the suffix is removed
def removeSuffix(word, suffix):
        if (word.endswith(suffix) == True):
                word = word[:-len(suffix)]
        return word

# removePrefix: given a string word and string prefix, 
# the prefix is removed
def removePrefix(word, prefix):
        if (word.startswith(prefix) == True):
                word = word[len(prefix):]
        return word

# parseProfile: takes a url of a profile, writing the last name, 
# first name, agency, and postion to stdout
def parseProfile(profile):
        for line in profile:
                if '<td>' in line:
                        info = line
                        info = info.strip(' ')   
                        info = info.strip('<td>')
                        # remove windows newline characters
                        info = info[:-2] 
                        info = removeSuffix(info, '</td>')
                        print(info),
                        if ',' not in info: print(','),
                if '</tbody>' in line:
                        return  
        return

# # # # # # # # # # # # # #
#          Main           #
# # # # # # # # # # # # # #
init_url = 'https://illinoiscomptroller.gov/financial-data/state-expenditures/employee-salary-database/?Issue_Year=2018&Agency=LEGISLATIVE&EmpId=&Last_Name=&Position=0'

# open webpage
page = urllib.urlopen(init_url)

# print column headings
print("LAST_NAME, FIRST_NAME, DIVISON, POSITION")

# declare array to store other url paths
paths = []

# declare array to store employee positions
positions = []

# Search initial home page for new url paths and positions, storing
# information in the according array
for line in page:
        if 'financial-data' and 'Issue_Year=2018' in line:
                curr_line = line
                if 'Last_Name=&' not in curr_line:
                        curr_line = curr_line.strip('<a href="')
                        # remove windows newline characters
                        curr_line = curr_line[:-2] 
                        curr_line = removeSuffix(curr_line, '=">')
                        paths.append(curr_line)
                if 'Last_Name=&' in curr_line:
                        position = page.readline()
                        position = position.strip(' ')
                        if (position != '\n'):
                                positions.append(position)
page.close()

# Search each url path for additional info, printing entire profile
# information to stdout
i = 0
for link in paths:
        link = 'https://illinoiscomptroller.gov' + link
        profile = urllib.urlopen(link)
        parseProfile(profile)
        profile.close()
        print positions[i],
        i += 1

exit()
