# Copyright (c) 2012 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {
    'conditions': [
      ['inside_chromium_build==0', {
        'webkit_src_dir': '../../../../..',
      },{
        'webkit_src_dir': '../../third_party/WebKit',
      }],
    ],
  },
  'includes': [
    '../appcache/webkit_appcache.gypi',
    '../blob/webkit_blob.gypi',
    '../database/webkit_database.gypi',
    '../dom_storage/webkit_dom_storage.gypi',
    '../fileapi/webkit_fileapi.gypi',
    '../quota/webkit_quota.gypi',
  ],
  'targets': [
    {
      'target_name': 'webkit_storage',
      'type': '<(component)',
      'variables': { 'enable_wexit_time_destructors': 1, },
      'dependencies': [
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/base/base.gyp:base_i18n',
        '<(DEPTH)/base/third_party/dynamic_annotations/dynamic_annotations.gyp:dynamic_annotations',
        '<(DEPTH)/build/temp_gyp/googleurl.gyp:googleurl',
        '<(DEPTH)/net/net.gyp:net',
        '<(DEPTH)/sql/sql.gyp:sql',
        '<(DEPTH)/third_party/sqlite/sqlite.gyp:sqlite',
        '<(DEPTH)/webkit/support/webkit_support.gyp:webkit_base',
        '<(webkit_src_dir)/Source/WebKit/chromium/WebKit.gyp:webkit',
      ],
      'defines': ['WEBKIT_STORAGE_IMPLEMENTATION'],
      'sources': [
        '../storage/webkit_storage_export.h',
        '<@(webkit_appcache_sources)',
        '<@(webkit_blob_sources)',
        '<@(webkit_database_sources)',
        '<@(webkit_dom_storage_sources)',
        '<@(webkit_fileapi_sources)',
        '<@(webkit_quota_sources)',
      ],
      'conditions': [
        ['OS=="lb_shell"', {
          'sources/': [
            # dom_storage
            ['exclude', 'dom_storage/session_storage_database.cc*'],

            # fileapi
            ['exclude', 'fileapi/syncable/sync_status_code.cc'],
            ['exclude', 'fileapi/syncable/sync_status_code.h'],
            ['exclude', 'fileapi/syncable/local_file_change_tracker.cc'],
            ['exclude', 'fileapi/syncable/local_file_change_tracker.h'],
            ['exclude', 'fileapi/file_system_directory_database.cc'],
            ['exclude', 'fileapi/file_system_directory_database.h'],
            ['exclude', 'fileapi/file_system_origin_database.cc'],
            ['exclude', 'fileapi/file_system_origin_database.h'],
            ['exclude', 'fileapi/obfuscated_file_util.cc'],
            ['exclude', 'fileapi/obfuscated_file_util.h'],
            ['exclude', 'fileapi/sandbox_mount_point_provider.cc'],
            ['exclude', 'fileapi/sandbox_mount_point_provider.h'],
          ],
          'include_dirs': [
            '../../../..', # for lbshell/src/ includes
          ]
        }],
        ['inside_chromium_build==0', {
          'dependencies': [
            '<(DEPTH)/webkit/support/setup_third_party.gyp:third_party_headers',
          ],
        }],
        ['"WTF_USE_LEVELDB=1" in feature_defines', {
          'dependencies': [
            '<(DEPTH)/third_party/leveldatabase/leveldatabase.gyp:leveldatabase',
          ],
          },
        ],
        ['chromeos==1', {
          'sources': [
            '<@(webkit_fileapi_chromeos_sources)',
          ],
        }],
        ['OS=="linux" or chromeos==1', {
          'sources': [
            '<@(webkit_fileapi_media_sources)',
          ],
        }],
      ],
    },
  ],
}
