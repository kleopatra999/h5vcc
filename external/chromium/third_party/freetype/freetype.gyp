{
  'targets': [
    {
      'target_name': 'ft2',
      'type': '<(library)',
      'defines': [
        'FT2_BUILD_LIBRARY',
      ],
      'copts': [
        '-Wall',
      ],
      'sources': [
        'src/autofit/autofit.c',
        'src/base/ftbase.c',
        'src/base/ftbbox.c',
        'src/base/ftbdf.c',
        'src/base/ftbitmap.c',
        'src/base/ftcid.c',
        'src/base/ftdebug.c',
        'src/base/ftfstype.c',
        'src/base/ftgasp.c',
        'src/base/ftglyph.c',
        'src/base/ftgxval.c',
        'src/base/ftinit.c',
        'src/base/ftlcdfil.c',
        'src/base/ftmm.c',
        'src/base/ftotval.c',
        'src/base/ftpatent.c',
        'src/base/ftpfr.c',
        'src/base/ftstroke.c',
        'src/base/ftsynth.c',
        'src/base/ftsystem.c',
        'src/base/fttype1.c',
        'src/base/ftwinfnt.c',
        'src/base/ftxf86.c',
        'src/bdf/bdf.c',
        'src/cache/ftcache.c',
        'src/cff/cff.c',
        'src/cid/type1cid.c',
        'src/gzip/ftgzip.c',
        'src/lzw/ftlzw.c',
        'src/pcf/pcf.c',
        'src/pfr/pfr.c',
        'src/psaux/psaux.c',
        'src/pshinter/pshinter.c',
        'src/psnames/psmodule.c',
        'src/raster/raster.c',
        'src/sfnt/sfnt.c',
        'src/smooth/smooth.c',
        'src/truetype/truetype.c',
        'src/type1/type1.c',
        'src/type42/type42.c',
        'src/winfonts/winfnt.c',
      ],
      'include_dirs': [
        'include',
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          'include',
        ],
      },
    },
  ],
}

# Local Variables:
# tab-width:2
# indent-tabs-mode:nil
# End:
# vim: set expandtab tabstop=2 shiftwidth=2:
