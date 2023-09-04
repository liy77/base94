{
  "targets": [
    {
      # myModule is the name of your native addon
      "target_name": "base94",
      "sources": ["src/base94.cpp"],
      'include_dirs': ["<!(node -p \"require('node-addon-api').include_dir\")"]
    }
  ]
}