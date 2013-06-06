<?php
/**
 * @file
 * localgov_planning.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function localgov_planning_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'openlylocal_planning_application_importer';
  $feeds_importer->config = array(
    'name' => 'OpenlyLocal planning application importer',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsJSONPathParser',
      'config' => array(
        'context' => '$.localgov_planning.*',
        'sources' => array(
          'jsonpath_parser:0' => 'uid',
          'jsonpath_parser:1' => 'description',
          'jsonpath_parser:2' => 'postcode',
          'jsonpath_parser:3' => 'address',
          'jsonpath_parser:4' => 'lat',
          'jsonpath_parser:5' => 'lng',
          'jsonpath_parser:7' => 'application_type',
          'jsonpath_parser:8' => 'url',
        ),
        'debug' => array(
          'options' => array(
            'context' => 0,
            'jsonpath_parser:0' => 0,
            'jsonpath_parser:1' => 0,
            'jsonpath_parser:2' => 0,
            'jsonpath_parser:3' => 0,
            'jsonpath_parser:4' => 0,
            'jsonpath_parser:5' => 0,
            'jsonpath_parser:7' => 0,
            'jsonpath_parser:8' => 0,
          ),
        ),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'jsonpath_parser:1',
            'target' => 'field_localgov_description',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'field_localgov_address:postal_code',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'field_localgov_address:locality',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'field_localgov_geolocation:lat',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'field_localgov_geolocation:lon',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'jsonpath_parser:7',
            'target' => 'field_localgov_application_type',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'jsonpath_parser:8',
            'target' => 'field_localgov_url:url',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '0',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'planning_application',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => 1800,
    'expire_period' => 3600,
    'import_on_create' => TRUE,
    'process_in_background' => FALSE,
  );
  $export['openlylocal_planning_application_importer'] = $feeds_importer;

  return $export;
}
