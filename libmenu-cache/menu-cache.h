/*
 *      menu-cache.h
 *      
 *      libmenu-cache is a small convinient library used to access 
 *      caches of freedesktop.org menus generated by menu-cache-gen.
 * 
 *      Copyright 2008 PCMan <pcman@thinkpad>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include <glib.h>

#ifndef __MENU_CACHE_H__
#define __MENU_CACHE_H__

G_BEGIN_DECLS

#define	MENU_CACHE_ITEM(x)	((MenuCacheItem*)x)
#define	MENU_CACHE_DIR(x)	((MenuCacheDir*)x)
#define	MENU_CACHE_APP(x)	((MenuCacheApp*)x)

typedef struct _MenuCacheItem MenuCacheItem;
typedef struct _MenuCacheDir MenuCacheDir;
typedef struct _MenuCacheApp MenuCacheApp;
typedef struct _MenuCache MenuCache;

typedef enum _MenuCacheType MenuCacheType;
enum _MenuCacheType
{
	MENU_CACHE_TYPE_NONE,
	MENU_CACHE_TYPE_DIR,
	MENU_CACHE_TYPE_APP,
	MENU_CACHE_TYPE_SEP
};

void menu_cache_init();

MenuCache* menu_cache_lookup( const char* menu_name );

/* Don't call this API directly. Use menu_cache_lookup instead. */
MenuCache* menu_cache_new( const char* cache_file, char** include, char** exclude );

MenuCache* menu_cache_ref(MenuCache* cache);
void menu_cache_unref(MenuCache* cache);

gboolean menu_cache_reload( MenuCache* cache );

MenuCacheDir* menu_cache_get_root_dir( MenuCache* cache );
MenuCacheDir* menu_cache_get_dir_from_path( MenuCache* cache, const char* path );

gpointer menu_cache_add_reload_notify(MenuCache* cache, GFunc func, gpointer user_data);
void menu_cache_remove_reload_notify(MenuCache* cache, gpointer notify_id);

gboolean menu_cache_file_is_updated( const char* menu_file );
gboolean menu_cache_is_updated( MenuCache* cache );


MenuCacheItem* menu_cache_item_ref(MenuCacheItem* item);
void menu_cache_item_unref(MenuCacheItem* item);

MenuCacheType menu_cache_item_get_type( MenuCacheItem* item );
const char* menu_cache_item_get_id( MenuCacheItem* item );
const char* menu_cache_item_get_name( MenuCacheItem* item );
const char* menu_cache_item_get_comment( MenuCacheItem* item );
const char* menu_cache_item_get_icon( MenuCacheItem* item );
const char* menu_cache_item_get_extended( MenuCacheItem* item, const char* key );
const char* menu_cache_item_get_qextended( MenuCacheItem* item, GQuark key );
MenuCacheDir* menu_cache_item_get_parent( MenuCacheItem* item );

GSList* menu_cache_dir_get_children( MenuCacheDir* dir );
const char* menu_cache_dir_get_file_basename( MenuCacheDir* dir );
const char* menu_cache_dir_get_file_dirname( MenuCacheDir* dir );
char* menu_cache_dir_make_path( MenuCacheDir* dir );

const char* menu_cache_app_get_file_dirname( MenuCacheApp* app );
const char* menu_cache_app_get_exec( MenuCacheApp* app );
const char* menu_cache_app_get_working_dir( MenuCacheApp* app );

/*
char** menu_cache_app_get_categories( MenuCacheApp* app );
*/

gboolean menu_cache_app_get_use_terminal( MenuCacheApp* app );
gboolean menu_cache_app_get_use_sn( MenuCacheApp* app );

/*
GSList* menu_cache_list_all_apps();
MenuCacheApp* menu_cache_find_app_by_exec( const char* exec );
*/

G_END_DECLS

#endif

