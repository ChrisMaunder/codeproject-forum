# The Code Project Discussion boards

The Discussion board ASP scripts as used in The Code Project. This is an open source project for the Code Project community.

![Sample Image - CodeProject-forum.jpg](https://raw.githubusercontent.com/ChrisMaunder/codeproject-forum/master/docs/assets/CodeProject-forum.jpg)

## Welcome to the CodeProject Discussion board scripts

## Introduction

This is the first of the "projects" that inspired the original concept of the Code Project.
We have provided these scripts to help developers, and we hope that developers such as 
yourself will help us in return by testing, submitting bug reports, suggesting improvements,
and submitting extensions.

We invite you to use these scripts in your own sites, but we ask that you keep the "powered
by CodeProject" logo in the top left corner. We also ask, in advance, for your patience and
understanding. These scripts will no doubt change a **lot**, so we suggest you check back
regularly to see the latest developments, or subscribe to the 
[Newsletter](http://www.codeproject.com/script/Newsletter/subscribe.asp) to receive
notifications of updates.

As of July 5, 2000 we are providing the source code to the ActiveX control that handles the
main work of organising the messages into a semblance of order. We would have loved to have
commented the code heavily, and even provide a step by step on how the code works, but
we simply haven't had the time, and decided that posting as-is is better than not posting at
all. If you find bugs or make improvements, please send them in.

> [!CAUTION]
> The ActiveX version of the code uses an ActiveX control was used to achieve this ordering by loading **all**
> messages in a forum and then ordering them correctly. This obviously results in poor performance once a forum starts
> growing. The pure ASP version Subsequent versions include a "SortOrder" field for each message, meaning the messages
>  are sorted at DB query time, and paging / filtering can be included to drasticaally reduce recordset sizes and load.
>  **It is not recommended to use the ActiveX version of this code**.

August 26, 2001 - [Philip Andrew](mailto:philip_andrew@hotmail.com) has supplied
a [PHP version](/CodeProject-php-forum.zip) of the forums.

## The Boards

The discussion board used at CodeProject was written by Uwe Keim, and comprises an
ActiveX control (written using Visual C++) and a set of ASP scripts. The ActiveX control
provides low level access to the forum message database and provides functionality to
ease the way in which parameters are passed from one page to another. The ActiveX control
is released in DLL form only at present, partly because we have not yet finished writing
it, and partly because we have barely even started documenting it :)

**New**: A new version of the boards has been written by Uwe that are ASP-only,
so no more messing around with ActiveX controls. The boards a minimal in implementation
but will give you everything you need to get a set of discussion boards up and running.
They are Access-only at the moment, but moving to SQLServer is a simple excercise left
to the reader. See the download section at the top of this page for the files.

So - onto the scripts. All discussions from here on will concentrate only on the
ActiveX version. The non-activeX version is sufficiently similar, though directory
structures and file nesting is a little different.

These are divided into a number of categories:

- **Application scripts** - these do the hard work
- **Include files** - these provide configuration, general routines and plug-in HTML
- **General user interface scripts** - these display the forum, provide means to add and edit
                                            messages, plus admin and error handling.

There is also:

- a directory of common images used by these forum scripts, as well as other scripts we will release
- a directory of common scripts that are also used by other scripts we will release
- a data directory, containing the forum database
- a bin directory, containing the ActiveX control

It's assumed that you are running NT4 Server or above with IIS4 or above, or Win9X with PWS.
The forum is stored in an Access database and uses the Jet Engine to access.

## Quick start

OK, so you've got the files and you want to start playing instead of reading the rest of this
article. I don't blame you. Here's what you do then:

1. Extract the zip file into a directory (say, 'CodeProject') ensuring that the directory structure
stored within the zip remains intact.
2. Register the ActiveX control in the `/CodeProject/forum/bin` directory
3. Edit `/CodeProject/common/config.asp` to suit your site.
4. Edit `/CodeProject/forum/includes/config.asp` to suit your discussion boards.
5. Ensure that your visitors have read and write access to the file 
   `/CodeProject/forum/data/forum.mdb`.
6. (Optional) Register an Email component on your system and edit 
    `/CodeProject/common/email.inc` to suit.

Now simply point your browser at `/CodeProject/forum/index.asp` and
you're away

## How it works

The scripts are made up of a set of main user interface scripts (in the root
directory) that make use of worker scripts (in the `/forum/app` directory)
to actually do the work. These in turn redirect the browser back to the user-interface
scripts.

The guts of the system is in `/forum/includes/forum.inc`. 
This file contains the definition of the forum class and is a wrapper 
for the main forum ActiveX control. This class is the main communication point 
that contains all forum-related functionality. You never communicate with the 
forum ActiveX control directly, but always indirectly via this class.

The class not only contains methods that perform the work, but also functions
to return URLs to the various application scripts. By doing this we are able to
set the names of the various scripts in the `/forum/includes/config.asp` 
file which makes it extremely simple to change the directory structure.

## Administering the forums

Each message has a password set by the author of that message that allows the author
to modify or delete a message. As well as this you can 
modify or delete messages by using the global password. This is defined in 
`/forum/includes/config.asp` and is used by simply appending a 
"`&ad=<password>`" onto the end of whatever URL you are currently
viewing.

For instance, if you are viewing the index of the forum with ID 1, and your
URL is `http://www.myserver.com/codeproject/forum/index.asp?forumid=1`
then to go into admin mode simply modify the URL to:

```cpp
http://www.myserver.com/codeproject/forum/index.asp?forumid=1&ad=12345
```

where "12345" is the password (defined in `/forum/includes/config.asp` 
as `ADMIN_PW`. This then gives you options to administer the forum (set
the forum name and description, as well as email address to be emailed when new 
messages or reply messages are posted).

To add or delete forums themselves you have to physically modify the database.
This is just one of those things we haven't yet done...

In admin mode you also get the option of modifying or deleting messages. Also, 
once in admin mode you will continue to be in admin mode as you move through the
forum scripts. Simply remove the "`&ad=<password>`" to step out of
admin mode.

## What's new...

The latest version of the scripts has an enhanced user interface, plus some
internal changes designed to fix a few problems with the first version. In a nut
shell:

- Message replies at the same level are now sorted in ascending order. This makes
the message view more intuitive
- "Preview" mode has been added, where the first few words of each message is
displayed under each message title
- The ActiveX control has been completely rewritten to be more efficient
- The user interface has been redesigned and cleaned up

## To do...

Too much. This is merely a sketch of the forums and does not even describe
what each file does, nor how we plan on expanding the scripts. We will constantly
be working on improvng these scripts and all extensions and modifications made
to the main CodeProject forums will be included in these downloadable files.

Consider this a work in progress!
