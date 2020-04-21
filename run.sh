waf_path="../waf"
export "NS_LOG=UdpServer=level_info|prefix_time|prefix_node|prefix_func:UdpClient=level_info|prefix_time|prefix_node|prefix_func"
${waf_path} --run Exercise3 > Exercise3Log.out 2>&1