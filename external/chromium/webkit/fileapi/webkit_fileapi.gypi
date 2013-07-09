# Copyright (c) 2012 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {
    'webkit_fileapi_sources': [
      '../fileapi/file_observers.h',
      '../fileapi/file_stream_writer.h',
      '../fileapi/file_system_callback_dispatcher.cc',
      '../fileapi/file_system_callback_dispatcher.h',
      '../fileapi/file_system_context.cc',
      '../fileapi/file_system_context.h',
      '../fileapi/file_system_dir_url_request_job.cc',
      '../fileapi/file_system_dir_url_request_job.h',
      '../fileapi/file_system_directory_database.cc',
      '../fileapi/file_system_directory_database.h',
      '../fileapi/file_system_file_stream_reader.cc',
      '../fileapi/file_system_file_stream_reader.h',
      '../fileapi/file_system_file_util.cc',
      '../fileapi/file_system_file_util.h',
      '../fileapi/file_system_file_util_proxy.cc',
      '../fileapi/file_system_file_util_proxy.h',
      '../fileapi/file_system_mount_point_provider.h',
      '../fileapi/file_system_operation.h',
      '../fileapi/file_system_operation_context.cc',
      '../fileapi/file_system_operation_context.h',
      '../fileapi/file_system_options.cc',
      '../fileapi/file_system_options.h',
      '../fileapi/file_system_origin_database.cc',
      '../fileapi/file_system_origin_database.h',
      '../fileapi/file_system_quota_client.cc',
      '../fileapi/file_system_quota_client.h',
      '../fileapi/file_system_quota_util.h',
      '../fileapi/file_system_task_runners.cc',
      '../fileapi/file_system_task_runners.h',
      '../fileapi/file_system_types.h',
      '../fileapi/file_system_url.cc',
      '../fileapi/file_system_url.h',
      '../fileapi/file_system_url_request_job.cc',
      '../fileapi/file_system_url_request_job.h',
      '../fileapi/file_system_url_request_job_factory.cc',
      '../fileapi/file_system_url_request_job_factory.h',
      '../fileapi/file_system_usage_cache.cc',
      '../fileapi/file_system_usage_cache.h',
      '../fileapi/file_system_util.cc',
      '../fileapi/file_system_util.h',
      '../fileapi/file_util_helper.cc',
      '../fileapi/file_util_helper.h',
      '../fileapi/file_writer_delegate.cc',
      '../fileapi/file_writer_delegate.h',
      '../fileapi/isolated_context.cc',
      '../fileapi/isolated_context.h',
      '../fileapi/isolated_file_util.cc',
      '../fileapi/isolated_file_util.h',
      '../fileapi/isolated_mount_point_provider.cc',
      '../fileapi/isolated_mount_point_provider.h',
      '../fileapi/local_file_stream_writer.cc',
      '../fileapi/local_file_stream_writer.h',
      '../fileapi/local_file_system_operation.cc',
      '../fileapi/local_file_system_operation.h',
      '../fileapi/local_file_util.cc',
      '../fileapi/local_file_util.h',
      '../fileapi/media/filtering_file_enumerator.cc',
      '../fileapi/media/filtering_file_enumerator.h',
      '../fileapi/media/media_path_filter.cc',
      '../fileapi/media/media_path_filter.h',
      '../fileapi/media/mtp_device_file_system_config.h',
      '../fileapi/media/native_media_file_util.cc',
      '../fileapi/media/native_media_file_util.h',
      '../fileapi/native_file_util.cc',
      '../fileapi/native_file_util.h',
      '../fileapi/obfuscated_file_util.cc',
      '../fileapi/obfuscated_file_util.h',
      '../fileapi/sandbox_file_stream_writer.cc',
      '../fileapi/sandbox_file_stream_writer.h',
      '../fileapi/sandbox_mount_point_provider.cc',
      '../fileapi/sandbox_mount_point_provider.h',
      '../fileapi/sandbox_quota_observer.cc',
      '../fileapi/sandbox_quota_observer.h',
      '../fileapi/syncable/file_change.cc',
      '../fileapi/syncable/file_change.h',
      '../fileapi/syncable/local_file_change_tracker.cc',
      '../fileapi/syncable/local_file_change_tracker.h',
      '../fileapi/syncable/local_file_sync_context.cc',
      '../fileapi/syncable/local_file_sync_context.h',
      '../fileapi/syncable/local_file_sync_status.cc',
      '../fileapi/syncable/local_file_sync_status.h',
      '../fileapi/syncable/local_origin_change_observer.h',
      '../fileapi/syncable/sync_callbacks.h',
      '../fileapi/syncable/sync_file_metadata.cc',
      '../fileapi/syncable/sync_file_metadata.h',
      '../fileapi/syncable/sync_file_status.h',
      '../fileapi/syncable/sync_file_type.h',
      '../fileapi/syncable/sync_operation_result.h',
      '../fileapi/syncable/sync_status_code.cc',
      '../fileapi/syncable/sync_status_code.h',
      '../fileapi/syncable/syncable_file_operation_runner.cc',
      '../fileapi/syncable/syncable_file_operation_runner.h',
      '../fileapi/syncable/syncable_file_system_operation.cc',
      '../fileapi/syncable/syncable_file_system_operation.h',
      '../fileapi/syncable/syncable_file_system_util.cc',
      '../fileapi/syncable/syncable_file_system_util.h',
      '../fileapi/task_runner_bound_observer_list.h',
      '../fileapi/test_mount_point_provider.cc',
      '../fileapi/test_mount_point_provider.h',
      '../fileapi/webfilewriter_base.cc',
      '../fileapi/webfilewriter_base.h',
    ],
    'webkit_fileapi_chromeos_sources': [
      '../chromeos/fileapi/async_file_stream.h',
      '../chromeos/fileapi/cros_mount_point_provider.cc',
      '../chromeos/fileapi/cros_mount_point_provider.h',
      '../chromeos/fileapi/file_access_permissions.cc',
      '../chromeos/fileapi/file_access_permissions.h',
      '../chromeos/fileapi/file_util_async.h',
      '../chromeos/fileapi/remote_file_system_operation.cc',
      '../chromeos/fileapi/remote_file_system_operation.h',
      '../chromeos/fileapi/remote_file_system_proxy.h',
      '../chromeos/fileapi/remote_file_stream_writer.cc',
      '../chromeos/fileapi/remote_file_stream_writer.h',
    ],
    'webkit_fileapi_media_sources': [
      '../fileapi/media/device_media_file_util.cc',
      '../fileapi/media/device_media_file_util.h',
      '../fileapi/media/mtp_device_delegate.h',
      '../fileapi/media/mtp_device_map_service.cc',
      '../fileapi/media/mtp_device_map_service.h',
    ],
  },
}
